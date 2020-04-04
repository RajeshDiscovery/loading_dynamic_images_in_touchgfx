#include <gui/common/BMPFileLoader.hpp>
#include <touchgfx/Color.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;


void BMPFileLoader::printBuffer(const char* buffer)
{
	cout << buffer << endl;

	//fstream file;
	//file.open("example.txt", ios::out | ios::in);
}

void BMPFileLoader::printBuffer(uint8_t *buffer , uint16_t len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%02x ", buffer[i]);
		//cout <<"0x"<<std::hex << (long)buffer[i] << " ";
	}
	cout << endl;
}

int BMPFileLoader::readFile(FileHdl hdl, uint8_t* const buffer, uint32_t length)
{
    uint32_t r = fread(buffer, 1, length, (FILE*)hdl);
    if (r != length)
    {
        return 1;
    }
    return 0;
}

void BMPFileLoader::seekFile(FileHdl hdl, uint32_t offset)
{
    fseek((FILE*)hdl, offset, SEEK_SET);
}

void BMPFileLoader::getBMP24Dimensions(FileHdl fileHandle, uint16_t& width, uint16_t& height)
{
    uint8_t data[50];
    seekFile(fileHandle, 0);
    readFile(fileHandle, data, 26); //read first part of header.
	printBuffer("getBMP24Dimensions");
	printBuffer(data, 26);



    width = data[18] | (data[19] << 8) | (data[20] << 16) | (data[21] << 24);
    height = data[22] | (data[23] << 8) | (data[24] << 16) | (data[25] << 24);

	printf("width=%d height =%d \r\n", width, height);


	/*cout << "width=" << (long)width << endl;
	cout << "height=" << (long)height << endl;*/

}

void BMPFileLoader::readBMP24File(Bitmap bitmap, FileHdl fileHandle)
{
    uint8_t data[50];
    seekFile(fileHandle, 0);
    readFile(fileHandle, data, 26); //read first part of header.

	FILE* fptr;

	// use appropriate location if you are using MacOS or Linux
	fptr = fopen("debug.txt", "w");




    const uint32_t offset = data[10] | (data[11] << 8) | (data[12] << 16) | (data[12] << 24);
    const uint32_t width = data[18] | (data[19] << 8) | (data[20] << 16) | (data[21] << 24);
    const uint32_t height = data[22] | (data[23] << 8) | (data[24] << 16) | (data[25] << 24);

	printf("offset=%d , width =%d height=%d \r\n", offset, width, height);

    readFile(fileHandle, data, offset - 26); //read rest of header.

    //get dynamic bitmap boundaries
    const uint32_t buffer_width = bitmap.getWidth();
    const uint32_t buffer_height = bitmap.getHeight();

	printf("buffer_height =%d buffer_width =%d \r\n", buffer_height, buffer_width);

    const uint32_t rowpadding = (4 - ((width * 3) % 4)) % 4;

    const Bitmap::BitmapFormat format = bitmap.getFormat();
    uint8_t* const  buffer8  = Bitmap::dynamicBitmapGetAddress(bitmap.getId());
    uint16_t* const buffer16 = (uint16_t*)buffer8;

    for (uint32_t y = 0; y < height; y++)
    {
        for (uint32_t x = 0; x < width; x++)
        {
            if (x % 10 == 0) //read data every 10 pixels = 30 bytes
            {
                if (x + 10 <= width) //read 10
                {
                    readFile(fileHandle, data, 10 * 3); //10 pixels
                }
                else
                {
                    readFile(fileHandle, data, (width - x) * 3 + rowpadding); //rest of line
                }
            }
			//printf("x =%d buffer_width =%d height =%d y =%d buffer_height=%d \r\n", x, buffer_width,
			//	height, y, buffer_height);

			if (fptr != NULL)
			{
				fprintf(fptr, "x =%d buffer_width =%d height =%d y =%d buffer_height=%d \r\n", x, buffer_width,\
					height, y, buffer_height);
				//fclose(fptr);
			}


            //insert pixel, if within dynamic bitmap boundaries
            if (x < buffer_width && ((height - y - 1) < buffer_height))
            {
				//printf("condition is not passed ..\r\n");
                switch (format)
                {
                case Bitmap::RGB565:
					//printf("Bitmap::RGB565 \r\n");

                    buffer16[x + (height - y - 1) * buffer_width] =
                        touchgfx::Color::getColorFrom24BitRGB(data[(x % 10) * 3 + 2], data[(x % 10) * 3 + 1], data[(x % 10) * 3]);
                    break;
                case Bitmap::RGB888:
                    {
						//printf("Bitmap::RGB888 \r\n");
                        //24 bit framebuffer
                        const uint32_t inx = 3 * (x + (height - y - 1) * buffer_width);
                        buffer8[inx + 0] = data[(x % 10) * 3 + 0];
                        buffer8[inx + 1] = data[(x % 10) * 3 + 1];
                        buffer8[inx + 2] = data[(x % 10) * 3 + 2];
                        break;
                    }
                case Bitmap::ARGB8888:
                    {
						//printf("Bitmap::ARGB8888 \r\n");
                        //24 bit framebuffer
                        const uint32_t inx = 4 * (x + (height - y - 1) * buffer_width);
                        buffer8[inx + 0] = data[(x % 10) * 3 + 0];
                        buffer8[inx + 1] = data[(x % 10) * 3 + 1];
                        buffer8[inx + 2] = data[(x % 10) * 3 + 2];
                        buffer8[inx + 3] = 255; //solid
                        break;
                    }
                default:
					printf("Unsupported bitmap format in BMPFileLoader! \r\n");
                    assert(!"Unsupported bitmap format in BMPFileLoader!");
                }
            }
			else
			{
				//printBuffer("else > x < buffer_width && ((height - y - 1) < buffer_height)");
			}
        }
    
	}

	if (fptr != NULL)
	{
		fclose(fptr);
	}

}
