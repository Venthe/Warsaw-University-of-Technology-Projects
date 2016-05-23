#pragma once
#include "object_handler.h"

void FillRect(bool random); // Fills drawing area with noise
void FillRect(Vector<int,2> a, Vector<int,2> b, Vector<unsigned char,3> color);
void FillRect(Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 0, 0, 0 })); // Fills whole drawing area with a certain color

void DrawModel(Model model, bool fill_polygons = false);
void DrawGrid(int density = 32, Vector<unsigned char, 3> color = Vector<unsigned char, 3>({ 32, 32, 32 }));

void Projection(double fov=config.camera.FocalLength, double aspectW=config.bufferSize[0], double aspectH = config.bufferSize[1], double clippingNear=0.05, double clippingFar=50.);

void LookAtNothing(Vector<double,3> up = Vector3::Up<double>(), Vector<double,3> cameraOrigin = config.camera.Origin);
void LookAt(Vector<double,3> lookat=Vector<double,3>(), Vector<double,3> up=Vector3::Up<double>(), Vector<double,3> cameraOrigin = config.camera.Origin);
void Viewport(int x = 0, int y = 0, int w = config.bufferSize[0], int h = config.bufferSize[1] );