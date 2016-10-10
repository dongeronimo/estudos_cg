#ifndef __texture_h
#define __texture_h
#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <glew.h>
namespace texture
{
	GLuint png_texture_load(const char * file_name, int * width, int * height)
	{
		// This function was originally written by David Grayson for
		// https://github.com/DavidEGrayson/ahrs-visualizer
		png_byte header[8];
		FILE *fp = fopen(file_name, "rb");
		if (fp == 0)
		{
			fclose(fp);
			throw std::runtime_error("arquivo not found " + std::string(file_name));
		}
		// read the header
		fread(header, 1, 8, fp);
		if (png_sig_cmp(header, 0, 8))
		{
			fclose(fp);
			throw std::runtime_error("is not a png " + std::string(file_name));
		}
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			fclose(fp);
			throw std::runtime_error("error: png_create_read_struct returned 0. " + std::string(file_name));
		}
		// create png info struct
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			throw std::runtime_error("error: png_create_info_struct returned 0 " + std::string(file_name));
		}
		// create png info struct
		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			fclose(fp);
			throw std::runtime_error("error: png_create_info_struct returned 0. " + std::string(file_name));
		}
		// the code in this if statement gets called if libpng encounters an error
		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			throw std::runtime_error("error from libpng " + std::string(file_name));
		}
		// init png reading
		png_init_io(png_ptr, fp);
		// let libpng know you already read the first 8 bytes
		png_set_sig_bytes(png_ptr, 8);
		// read all the info up to the image data
		png_read_info(png_ptr, info_ptr);
		// variables to pass to get info
		int bit_depth, color_type;
		png_uint_32 temp_width, temp_height;
		// get info about png
		png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
			NULL, NULL, NULL);
		if (width) { *width = temp_width; }
		if (height) { *height = temp_height; }
		//printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);
		if (bit_depth != 8)
		{
			throw std::runtime_error("Unsupported bit depth %d.  Must be 8. " + std::string(file_name));
			return 0;
		}
		GLint format;
		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			throw std::runtime_error("PNG_COLOR_TYPE_GRAY " + std::string(file_name));
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			throw std::runtime_error("PNG_COLOR_TYPE_GRAY_ALPHA " + std::string(file_name));
			break;
		case PNG_COLOR_TYPE_PALETTE:
			throw std::runtime_error("PNG_COLOR_TYPE_PALETTE " + std::string(file_name));
			break;
		case PNG_COLOR_TYPE_RGB:
			format = GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			format = GL_RGBA;
			break;
		default:
			throw std::runtime_error("Unknown libpng color type  " + std::string(file_name));
			return 0;
		}
		// Update the png info struct.
		png_read_update_info(png_ptr, info_ptr);
		// Row size in bytes.
		int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
		// glTexImage2d requires rows to be 4-byte aligned
		rowbytes += 3 - ((rowbytes - 1) % 4);
		// Allocate the image_data as a big block, to be given to opengl
		png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte) + 15);
		if (image_data == NULL)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			throw std::runtime_error("error: could not allocate memory for PNG image data  " + std::string(file_name));
		}
		// row_pointers is for pointing to image_data for reading the png with libpng
		png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
		if (row_pointers == NULL)
		{
			fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			free(image_data);
			fclose(fp);
			return 0;
		}
		// set the individual row_pointers to point at the correct offsets of image_data
		for (unsigned int i = 0; i < temp_height; i++)
		{
			row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
		}
		// read the png into image_data through row_pointers
		png_read_image(png_ptr, row_pointers);
		// Generate the OpenGL texture object
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// clean up
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		free(image_data);
		free(row_pointers);
		fclose(fp);
		return texture;
	}
}
#endif