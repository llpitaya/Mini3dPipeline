#include"Device.h"
#include<cassert>
Device::Device(int w, int h, void * fb) :transform(w,h)
{
	Init(w, h, fb);
}

Device::~Device()
{
	if (this->frameBuf!=nullptr)
	{
		free(frameBuf);
	}
	frameBuf = nullptr;
	zBuf = nullptr;
	texture = nullptr;
}

void Device::SetTexture(void * texBuf, int w, int h, long pitch)
{
	assert(w < 1024 && h < 1024);
	uint8 * ptr = (uint8*)texBuf;
	for (size_t i = 0; i < height; i++,ptr+=pitch)
	{
		texture[i] = (uint32*)ptr;
	}
	this->tex_width = w;
	this->tex_height = h;
	this->max_u = (float)(w - 1);
	this->max_v = (float)(h - 1);
}

void Device::ClearBuf(int mode)
{
	ClearZBuf();
	ClearFrameBuf(mode);
}

void Device::DrawPoint(int x, int y, const uint32& color)
{
	if (x<width && y<height)
	{
		frameBuf[x][y] = color;
	}
}

void Device::DrawLine(int x1, int y1, int x2, int y2, const uint32& color)
{
	if (x1==x2 && y1==y2)
	{
		DrawPoint(x1, y1, color);
	}
	else if (y1==y2)
	{
		int step = x1 < x2 ? 1 : -1;
		for (int i = x1; i != x2; i += step)
		{
			DrawPoint(i, y1, color);
		}
		DrawPoint(x2, y2, color);
	}
	else if (x1==x2)
	{
		int step = y1 < y2 ? 1 : -1;
		for (int y = y1; y != y2; y += step)
		{
			DrawPoint(x1, y, color);
		}
		DrawPoint(x2, y2, color);
	}
	else
	{

	}
}

void Device::ReadTexture(float u, float v)
{

}

void Device::DrawScanline(const scanline_t & scanline)
{
	
}

void Device::RenderTrap(trapezoid_t & trap)
{

}

void Device::DrawPrimitive(const Vertex &v1, const Vertex& v2, const Vertex& v3)
{

}

//设备初始化
void Device::Init(int w, int h, void * fb)
{
	int memorySize = sizeof(void*) * (2 * h + 1024) + w * h * 8;
	uint8 *ptr = (uint8*)malloc(memorySize);
	uint8 * fBuf, *zBuf;
	assert(ptr);
	this->frameBuf = (uint32 **)ptr;
	this->zBuf = (float **)(ptr + h);
	ptr += sizeof(void*) * 2 * h;
	this->texture = (uint32**)ptr;
	ptr += sizeof(void*) * 1024;
	
	fBuf = (uint8*)ptr;
	zBuf = (uint8*)ptr + w * h * 4;
	ptr += width * height * 8;

	if (fb!=nullptr)
	{
		fBuf =(uint8*)fb; //将fBuf指向外部帧缓存fb
	}

	for (uint32 i = 0; i < h; i++)
	{
		this->frameBuf[i] = (uint32*)(fBuf + i * width * 4);
		this->zBuf[i] = (float*)(fBuf + i * width * 4);
	}

	this->texture[0] = (uint32*)ptr; // ????????????
	this->texture[1] = (uint32*)(ptr + 16); // ??????????
	memset(this->texture[0], 0, 64);

	this->width = w;
	this->height = h;
	this->tex_height = 2; //?
	this->tex_width = 2; //?
	this->max_u = 1.0f;
	this->max_v = 1.0f;
	this->background = 0x00ff00ff;
	this->foreground = 0x00000000;
	//this->transform = Transform(w,h);
}

void Device::ClearZBuf()
{
	for (size_t i = 0; i < height; i++)
	{
		float * dst = this->zBuf[i];
		for (size_t j = 0; j < width; j++)
		{
			dst[j] = 0.0f;
		}
	}
}

void Device::ClearFrameBuf(int mode)
{
	for (size_t i = 0; i < height; i++)
	{
		uint32 * dst = this->frameBuf[i];
		uint32 cc = (height - 1 - i) / (height - 1);
		cc = (cc < 16) | (cc << 8) | (cc); // ??
		if (mode == 0)
		{
			cc = this->background;
		}
		for (size_t j = 0; j < width; j++)
		{
			dst[j] = cc;
		}
	}
}