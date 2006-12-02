/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: MeshObject.h,v $
  Language:  C++
  Date:      $Date: 2006/12/02 04:22:15 $
  Version:   $Revision: 1.1 $
  Copyright (c) 2003 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.
=========================================================================*/
#ifndef __MeshObject_h_
#define __MeshObject_h_

// Forward references
class IRISApplication;
class GlobalState;
class IRISImageData;
class ColorLabel;
class AllPurposeProgressAccumulator;

namespace itk {
  class Command;
}

#include "SNAPCommon.h"
#include "AllPurposeProgressAccumulator.h"
#include <vector>

/**
 * \class MeshObject
 * \brief A class representing a mesh generated from a segmentation.
 *
 * This class wraps around IRISMeshPipeline and LevelSetMeshPipeline.  It's a very
 * high level class that generates a correct mesh based on the current state of the 
 * application.
 */
class MeshObject  {
private:
  // The number of allocated display lists
  unsigned int m_DisplayListNumber;

  // The starting display list number
  unsigned int m_DisplayListIndex;

  // The labels associated with the allocated display lists
  std::vector<LabelType> m_Labels;

  /** 
   * This method applies the settings in a color label if color label 
   * is displayable
   */
  bool ApplyColorLabel(const ColorLabel &label);

  // Back pointer to the application object
  IRISApplication *m_Driver;

  // Pointer to the global state object
  GlobalState *m_GlobalState;

  // Progress accumulator for multi-object rendering
  itk::SmartPointer<AllPurposeProgressAccumulator> m_Progress;

public:
  MeshObject();
  MeshObject( const MeshObject& M ) { *this=M; } 
  MeshObject& operator= ( const MeshObject& M ) { *this=M; return *this; }
  ~MeshObject();

  void Reset();

  /**
   * Initialize the object with an IRISApplication pointer
   */
  void Initialize(IRISApplication *driver);

  /* MeshObject::GenerateMesh();
   *
   * DESCRIPTION:
   * This function generates a mesh which represents a 3D 
   * segmentation. This operation is accomplished by retrieving 
   * the image data from the IRISImageData structure and then 
   * invoking a VTK isosurface extraction algorithm. To create 
   * the surface it performs the following steps (GB, MS, TMR 
   * are optional): 
   *   1.Gaussian Blur on the imported image data 
   *   2.Triangle generation using a contour algorithm 
   *   3.Mesh Smoothing 
   *   4.Triangle Mesh Reduction 
   *   5.Triangle stripping
   *
   * Modified by Konstantin Bobkov and Nathan Moon (April 2002)
   * New modification of this method allows to generate 
   * trianglemesh for the Snake Voxel Data. In this case the
   * Gaussian Blur step on the imported SnakeVoxData is not
   * performed
   * 
   * PRECONDITIONS:
   * - Valid Segmented VoxData or SnakeVoxData
   *
   * POSTCONDITIONS:
   * - A displaylist (points) and a trianglemesh 
   */
  void GenerateMesh(itk::Command *command);

  /* MeshObject::Display();
   *
   * DESCRIPTION:
   * This function displays the mesh generated by the 
   * GenerateMesh() method described above
   *
   * Modified by Konstantin Bobkov (April 2002)
   * New modification of this method allows to display the
   * currently generated trianglemesh for the Snake Voxel Data. 
   *
   * 
   * PRECONDITIONS:
   * - for each segmented object to be displayed the mesh is valid
   *
   * POSTCONDITIONS:
   * - each object in displaylist is displayed 
   */
  void Display();
};

#endif // __MeshObject_h_

/*
 *$Log: MeshObject.h,v $
 *Revision 1.1  2006/12/02 04:22:15  pyushkevich
 *Initial sf checkin
 *
 *Revision 1.1.1.1  2006/09/26 23:56:18  pauly2
 *Import
 *
 *Revision 1.8  2005/10/29 14:00:14  pauly
 *ENH: SNAP enhacements like color maps and progress bar for 3D rendering
 *
 *Revision 1.7  2003/10/09 22:45:13  pauly
 *EMH: Improvements in 3D functionality and snake parameter preview
 *
 *Revision 1.6  2003/10/02 14:54:53  pauly
 *ENH: Development during the September code freeze
 *
 *Revision 1.1  2003/09/11 13:50:29  pauly
 *FIX: Enabled loading of images with different orientations
 *ENH: Implemented image save and load operations
 *
 *Revision 1.4  2003/08/28 14:37:09  pauly
 *FIX: Clean 'unused parameter' and 'static keyword' warnings in gcc.
 *FIX: Label editor repaired
 *
 *Revision 1.3  2003/08/27 14:03:21  pauly
 *FIX: Made sure that -Wall option in gcc generates 0 warnings.
 *FIX: Removed 'comment within comment' problem in the cvs log.
 *
 *Revision 1.2  2003/08/27 04:57:46  pauly
 *FIX: A large number of bugs has been fixed for 1.4 release
 *
 *Revision 1.1  2003/07/12 04:52:25  pauly
 *Initial checkin of SNAP application  to the InsightApplications tree
 *
 *Revision 1.7  2003/07/12 01:34:18  pauly
 *More final changes before ITK checkin
 *
 *Revision 1.6  2003/07/11 23:29:17  pauly
 **** empty log message ***
 *
 *Revision 1.5  2003/07/11 21:25:12  pauly
 *Code cleanup for ITK checkin
 *
 *Revision 1.4  2003/06/08 16:11:42  pauly
 *User interface changes
 *Automatic mesh updating in SNAP mode
 *
 *Revision 1.3  2003/05/05 12:30:18  pauly
 **** empty log message ***
 *
 *Revision 1.2  2003/04/18 17:32:18  pauly
 **** empty log message ***
 *
 *Revision 1.1  2003/03/07 19:29:47  pauly
 *Initial checkin
 *
 *Revision 1.1.1.1  2002/12/10 01:35:36  pauly
 *Started the project repository
 *
 *
 *Revision 1.4  2002/04/27 17:49:00  bobkov
 *Added comments
 *
 *Revision 1.3  2002/04/11 23:09:15  bobkov
 *Commented GenerateMesh() method
 *
 *Revision 1.2  2002/03/08 14:06:29  moon
 *Added Header and Log tags to all files
 **/
