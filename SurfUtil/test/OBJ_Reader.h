//
//  Copyright@2013, Illinois Rocstar LLC. All rights reserved.
//        
//  See LICENSE file included with this source or
//  (opensource.org/licenses/NCSA) for license information. 
//

#ifndef OBJ_READER_H
#define OBJ_READER_H

#include "surfbasic.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>

COM_EXTERN_MODULE(SimIN);

// This class provides an interface for reading in a surface mesh 
// from the ".smf" or ".obj" file.
class OBJ_Reader {
public:
  // Constructor from an MPI communicator and a scale factor.
  OBJ_Reader()  {}

  // Assuming the window has been created, read in the local panes from
  // given file and return the number of local panes.
  int read_mesh( const char *fname, const std::string &wname) {
    std::ifstream is( fname); 
    if ( is.bad()) {
      std::cerr << "Error: Could not open file " << fname << std::endl;
      exit(-1);
    }

    // Create the window if not yet exist
    int h=COM_get_window_handle(wname.c_str());
    if ( h<=0) COM_new_window( wname.c_str());

    std::cout << "Reading file " << fname << std::endl;

    int nn, ne;
    get_nextline( is, buf);
    std::sscanf( buf, "%d %d", &nn, &ne);

    std::cout << "Reading " << nn << " nodes and " 
	      << ne << " triangles " << std::endl;
    read_pane_coors( is, wname, nn);
    read_pane_elems( is, wname, ne);

    return 1;
  }

private:
  void get_nextline( std::istream &is, char *str) {
    str[0] = '\0';
    if ( is.eof()) { return; }
    is.getline( str, MAXLEN); 
  }

  // Read in coordinates of a pane into a window if local
  void read_pane_coors( std::istream &is, const std::string &wname, int nn) {
    COM_set_size( (wname+".nc").c_str(), 1, nn);
    SURF::Point_3<double> *ps;
    COM_allocate_array( (wname+".nc").c_str(), 1, &(void*&)ps);
    
    for ( int i=0; i<nn; ++i) {
      get_nextline( is, buf); 
      std::sscanf( buf, "%lf %lf %lf", &ps[i][0], &ps[i][1], &ps[i][2]);
    }
  }

  // Read in element connectivity of a pane into a window if local
  void read_pane_elems( std::istream &is, const std::string &wname, int ne){
    // Note: Only supports triangular meshes now.
    COM_set_size( (wname+".:t3:").c_str(), 1, ne);
    SURF::Vector_3<int> *es;
    COM_allocate_array( (wname+".:t3:").c_str(), 1, &(void*&)es);
    
    for (int i=0; i<ne; ++i) {
      get_nextline( is, buf); 
      std::sscanf( buf, "%d %d %d", &es[i][0], &es[i][1], &es[i][2]);
    }
  }

private:
  enum  {MAXLEN=255};
  char  buf[MAXLEN+1];
};

#endif



