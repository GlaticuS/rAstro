#ifndef 2DG_H_INCLUDED
#define 2DG_H_INCLUDED
RGBTRIPLE* loadBMP(const char *, int, int ); //функция загрузки файла
RGBTRIPLE normalizeRGBT(int, int , int );
bool saveBMP(const char *, RGBTRIPLE *, int, int);
RGBTRIPLE* ex(RGBTRIPLE *, int, int, float, float);
RGBTRIPLE* reflectionX(RGBTRIPLE *, int, int);
RGBTRIPLE* reflectionY(RGBTRIPLE *, int, int);
RGBTRIPLE* reflectionXY(RGBTRIPLE *, int, int);
RGBTRIPLE* rot(RGBTRIPLE *, int, int, int);
RGBTRIPLE* matrixConvolution(RGBTRIPLE *, int , int , int **, int );
RGBTRIPLE* matrixConvolution1(RGBTRIPLE *, int, int , double **, int );

#endif // 2DG_H_INCLUDED
