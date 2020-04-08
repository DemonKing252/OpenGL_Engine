#pragma once
class PerlinNoise
{
public:
	static void GeneratePerlinNoise(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput);
};

