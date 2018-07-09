#ifndef DEVICE_H
#define DEVICE_H
#include"common.h"
#include"Vextex.h"
#include"Transform.h"

class Device
{
public:
	Device(int w, int h, void * fb);
	~Device();
	void SetTexture(void * texBuf, int w, int h, long pitch);
	void ClearBuf(int mode);
	void DrawPoint(int x, int y, const uint32& color);
	void DrawLine(int x1, int y1, int x2, int y2, const uint32& color);
	void ReadTexture(float u, float v);
	void DrawScanline(const scanline_t & scanline);
	void RenderTrap(trapezoid_t & trap);
	void DrawPrimitive(const Vertex &v1, const Vertex& v2, const Vertex& v3);


private:
	void Init(int w, int h, void * fb);
	void ClearZBuf();
	void ClearFrameBuf(int mode);
	Transform transform;
	int width;//窗口宽度
	int height;//窗口高度
	uint32 ** frameBuf;
	float ** zBuf;
	uint32 ** texture;
	int tex_width;
	int tex_height;
	float max_u;
	float max_v;
	RENDER_STATE render_state;
	uint32 background;
	uint32 foreground;
};

#endif