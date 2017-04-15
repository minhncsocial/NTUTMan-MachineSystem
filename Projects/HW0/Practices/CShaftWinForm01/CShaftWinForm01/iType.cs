using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct iIPoint
{
    public uint x;
    public uint y;
}

[StructLayout(LayoutKind.Sequential)]
public struct iDPoint
{
    public double x;
    public double y;
}

[StructLayout(LayoutKind.Sequential)]
public struct mRect
{
	public int  top;
	public int  bottom;
	public int  left;
	public int  right;
}

[StructLayout(LayoutKind.Sequential)]
public struct NCCFind
{
	public int		Width;
	public int		Height;

	public double     CX;
	public double     CY;
	public double	    Angle;
	public double	    Scale;
	public double	    Score;
}

[StructLayout(LayoutKind.Sequential)]
public struct GeoFind
{
    public double x;
    public double y;
    public double Score;
    public double Angle;
    public double Scale;
}