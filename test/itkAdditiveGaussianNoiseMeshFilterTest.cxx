/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include <itkMesh.h>
#include <itkRegularSphereMeshSource.h>
#include <itkAdditiveGaussianNoiseMeshFilter.h>
#include "itkTestingMacros.h"

int
itkAdditiveGaussianNoiseMeshFilterTest(int itkNotUsed(argc), char * itkNotUsed(argv) [])
{

  typedef double     TPixel;
  const unsigned int Dimension = 3;

  //////////////
  // Typedefs //
  //////////////

  typedef itk::Mesh< TPixel, Dimension >                TMesh;
  typedef itk::RegularSphereMeshSource< TMesh >         TSphere;
  typedef itk::AdditiveGaussianNoiseMeshFilter< TMesh > TNoise;

  ////////////////
  // Parameters //
  ////////////////

  const int SPHERE_RESOLUTION = 5;
  const double SPHERE_SCALE = 10.0;

  const int NOISE_SEED = 100;
  const TMesh::CoordRepType NOISE_SIGMA = SPHERE_SCALE * 0.01;
  const TMesh::CoordRepType NOISE_MEAN = 1.0;

  ///////////
  // Logic //
  ///////////

  TSphere::Pointer sphere = TSphere::New();

  sphere->SetResolution( SPHERE_RESOLUTION );
  sphere->SetScale( SPHERE_SCALE );

  TNoise::Pointer noise = TNoise::New();

  EXERCISE_BASIC_OBJECT_METHODS( noise,
                                 AdditiveGaussianNoiseMeshFilter,
                                 MeshToMeshFilter );

  noise->SetInput( sphere->GetOutput() );
  noise->SetSeed( NOISE_SEED );
  TEST_SET_GET_VALUE( NOISE_SEED, noise->GetSeed() );
  noise->SetSigma( NOISE_SIGMA );
  TEST_SET_GET_VALUE( NOISE_SIGMA, noise->GetSigma() );
  noise->SetMean( NOISE_MEAN );
  TEST_SET_GET_VALUE( NOISE_MEAN, noise->GetMean() );

  noise->Update();

  return EXIT_SUCCESS;

}