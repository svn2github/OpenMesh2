#include <gtest/gtest.h>
#include <Unittests/unittests_common.hh>

#include <iostream>

namespace {

class OpenMeshTrimeshCirculatorFaceEdge : public OpenMeshBase {

    protected:

        // This function is called before each test is run
        virtual void SetUp() {
        }

        // This function is called after all tests are through
        virtual void TearDown() {

            // Do some final stuff with the member data here...
        }


    // Member already defined in OpenMeshBase
    //Mesh mesh_;  
};

/*
 * ====================================================================
 * Define tests below
 * ====================================================================
 */




/*
 * Small FaceEdgeIterator Test
 */
TEST_F(OpenMeshTrimeshCirculatorFaceEdge, FaceEdgeIterWithoutHolesIncrement) {

  mesh_.clear();

  // Add some vertices
  Mesh::VertexHandle vhandle[6];

  vhandle[0] = mesh_.add_vertex(Mesh::Point(0, 1, 0));
  vhandle[1] = mesh_.add_vertex(Mesh::Point(1, 0, 0));
  vhandle[2] = mesh_.add_vertex(Mesh::Point(2, 1, 0));
  vhandle[3] = mesh_.add_vertex(Mesh::Point(3, 0, 0));
  vhandle[4] = mesh_.add_vertex(Mesh::Point(4, 1, 0));
  vhandle[5] = mesh_.add_vertex(Mesh::Point(2,-1, 0));

  // Add three faces
  std::vector<Mesh::VertexHandle> face_vhandles;

  face_vhandles.push_back(vhandle[0]);
  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[2]);
  mesh_.add_face(face_vhandles);

  face_vhandles.clear();

  face_vhandles.push_back(vhandle[2]);
  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[3]);
  mesh_.add_face(face_vhandles);

  face_vhandles.clear();

  face_vhandles.push_back(vhandle[2]);
  face_vhandles.push_back(vhandle[3]);
  face_vhandles.push_back(vhandle[4]);
  mesh_.add_face(face_vhandles);

  face_vhandles.clear();

  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[5]);
  face_vhandles.push_back(vhandle[3]);
  mesh_.add_face(face_vhandles);

  /* Test setup:
   *
   * 0 ------ 2 ------ 4
   *  \      / \      /
   *   \  0 /   \  2 /
   *    \  /  1  \  /
   *     1 ------- 3
   *      \       /
   *       \  3  /
   *        \   /
   *         \ /
   *          5
   */


  Mesh::FaceEdgeIter fe_it  = mesh_.fe_begin(mesh_.face_handle(1));
  Mesh::FaceEdgeIter fe_end = mesh_.fe_end(mesh_.face_handle(1));

  EXPECT_EQ(4, fe_it->idx() ) << "Index wrong in FaceEdgeIter at initialization";
  EXPECT_TRUE(fe_it.is_valid()) << "Iterator invalid in FaceEdgeIter at initialization";
  ++fe_it;
  EXPECT_EQ(1, fe_it->idx() ) << "Index wrong in FaceEdgeIter at step 1";
  EXPECT_TRUE(fe_it.is_valid()) << "Iterator invalid in FaceEdgeIter at step 1";
  ++fe_it;
  EXPECT_EQ(3, fe_it->idx() ) << "Index wrong in FaceEdgeIter at step 2";
  EXPECT_TRUE(fe_it.is_valid()) << "Iterator invalid in FaceEdgeIter at step 2";
  ++fe_it;
  EXPECT_EQ(4, fe_it->idx() ) << "Index wrong in FaceEdgeIter at end";
  EXPECT_FALSE(fe_it.is_valid()) << "Iterator invalid in FaceEdgeIter at end";
  EXPECT_TRUE( fe_it == fe_end )  << "End iterator for FaceEdgeIter not matching";

  Mesh::ConstFaceEdgeIter cfe_it  = mesh_.cfe_begin(mesh_.face_handle(1));
  Mesh::ConstFaceEdgeIter cfe_end = mesh_.cfe_end(mesh_.face_handle(1));

  EXPECT_EQ(4, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at initialization";
  EXPECT_TRUE(cfe_it.is_valid()) << "Iterator invalid in ConstFaceEdgeIter at initialization";
  ++cfe_it;
  EXPECT_EQ(1, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at step 1";
  EXPECT_TRUE(cfe_it.is_valid()) << "Iterator invalid in ConstFaceEdgeIter at step 1";
  ++cfe_it;
  EXPECT_EQ(3, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at step 2";
  EXPECT_TRUE(cfe_it.is_valid()) << "Iterator invalid in ConstFaceEdgeIter at step 2";
  ++cfe_it;
  EXPECT_EQ(4, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at end";
  EXPECT_FALSE(cfe_it.is_valid()) << "Iterator invalid in ConstFaceEdgeIter at end";
  EXPECT_TRUE( cfe_it == cfe_end )  << "End iterator for ConstFaceEdgeIter not matching";

}
}


/*
 * Test if the end iterator stays invalid after one lap
 */
TEST_F(OpenMeshTrimeshCirculatorFaceEdge, FaceEdgeIterCheckInvalidationAtEnds) {

  mesh_.clear();

   // Add some vertices
   Mesh::VertexHandle vhandle[5];

   vhandle[0] = mesh_.add_vertex(Mesh::Point(0, 1, 0));
   vhandle[1] = mesh_.add_vertex(Mesh::Point(1, 0, 0));
   vhandle[2] = mesh_.add_vertex(Mesh::Point(2, 1, 0));
   vhandle[3] = mesh_.add_vertex(Mesh::Point(0,-1, 0));
   vhandle[4] = mesh_.add_vertex(Mesh::Point(2,-1, 0));

   // Add two faces
   std::vector<Mesh::VertexHandle> face_vhandles;

   face_vhandles.push_back(vhandle[0]);
   face_vhandles.push_back(vhandle[1]);
   face_vhandles.push_back(vhandle[2]);
   Mesh::FaceHandle fh0 = mesh_.add_face(face_vhandles);

   face_vhandles.clear();

   face_vhandles.push_back(vhandle[1]);
   face_vhandles.push_back(vhandle[3]);
   face_vhandles.push_back(vhandle[4]);
   mesh_.add_face(face_vhandles);

   face_vhandles.clear();

   face_vhandles.push_back(vhandle[0]);
   face_vhandles.push_back(vhandle[3]);
   face_vhandles.push_back(vhandle[1]);
   mesh_.add_face(face_vhandles);

   face_vhandles.clear();

   face_vhandles.push_back(vhandle[2]);
   face_vhandles.push_back(vhandle[1]);
   face_vhandles.push_back(vhandle[4]);
   mesh_.add_face(face_vhandles);

   /* Test setup:
       0 ==== 2
       |\  0 /|
       | \  / |
       |2  1 3|
       | /  \ |
       |/  1 \|
       3 ==== 4 */


  // Check if the end iterator stays invalid after end
  Mesh::FaceEdgeIter endIter = mesh_.fe_end(fh0);
  EXPECT_FALSE(endIter.is_valid()) << "EndIter is not invalid";
  ++endIter ;
  EXPECT_FALSE(endIter.is_valid()) << "EndIter is not invalid after increment";

  // Check if the end iterators becomes valid after decrement
  endIter = mesh_.fe_end(fh0);
  EXPECT_FALSE(endIter.is_valid()) << "EndIter is not invalid";
  --endIter;
  EXPECT_TRUE(endIter.is_valid()) << "EndIter is invalid after decrement";
  EXPECT_EQ(1,endIter->idx()) << "EndIter points on the wrong element";


  // Check if the start iterator decrement is invalid
  Mesh::FaceEdgeIter startIter = mesh_.fe_begin(fh0);
  EXPECT_TRUE(startIter.is_valid()) << "StartIter is not valid";
  --startIter;
  EXPECT_FALSE(startIter.is_valid()) << "StartIter decrement is not invalid";

  // Check if the start iterator becomes valid
  ++startIter;
  EXPECT_TRUE(startIter.is_valid()) << "StartIter is invalid after re-incrementing";
  EXPECT_EQ(startIter->idx(), mesh_.fe_begin(fh0)->idx()) << "StartIter points on the wrong element";

}


/*
 * Small FaceEdgeIterator Test
 */
/*
TEST_F(OpenMeshTrimeshCirculatorFaceEdge, FaceEdgeIterWithoutHolesDecrement) {

  mesh_.clear();

  // Add some vertices
  Mesh::VertexHandle vhandle[6];

  vhandle[0] = mesh_.add_vertex(Mesh::Point(0, 1, 0));
  vhandle[1] = mesh_.add_vertex(Mesh::Point(1, 0, 0));
  vhandle[2] = mesh_.add_vertex(Mesh::Point(2, 1, 0));
  vhandle[3] = mesh_.add_vertex(Mesh::Point(3, 0, 0));
  vhandle[4] = mesh_.add_vertex(Mesh::Point(4, 1, 0));
  vhandle[5] = mesh_.add_vertex(Mesh::Point(2,-1, 0));

  // Add three faces
  std::vector<Mesh::VertexHandle> face_vhandles;

  face_vhandles.push_back(vhandle[0]);
  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[2]);
  mesh_.add_face(face_vhandles);

  face_vhandles.clear();

  face_vhandles.push_back(vhandle[2]);
  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[3]);
  mesh_.add_face(face_vhandles);

  face_vhandles.clear();

  face_vhandles.push_back(vhandle[2]);
  face_vhandles.push_back(vhandle[3]);
  face_vhandles.push_back(vhandle[4]);
  mesh_.add_face(face_vhandles);

  face_vhandles.clear();

  face_vhandles.push_back(vhandle[1]);
  face_vhandles.push_back(vhandle[5]);
  face_vhandles.push_back(vhandle[3]);
  mesh_.add_face(face_vhandles);
*/
  /* Test setup:
   *
   * 0 ------ 2 ------ 4
   *  \      / \      /
   *   \  0 /   \  2 /
   *    \  /  1  \  /
   *     1 ------- 3
   *      \       /
   *       \  3  /
   *        \   /
   *         \ /
   *          5
   */

/*
  Mesh::FaceEdgeIter fe_it  = mesh_.fe_begin(mesh_.face_handle(1));
  Mesh::FaceEdgeIter fe_end = mesh_.fe_end(mesh_.face_handle(1));

  EXPECT_EQ(4, fe_it->idx() ) << "Index wrong in FaceEdgeIter at initialization";
  EXPECT_TRUE(fe_it) << "Iterator invalid in FaceEdgeIter at initialization";
  --fe_it;
  EXPECT_EQ(1, fe_it->idx() ) << "Index wrong in FaceEdgeIter at step 1";
  EXPECT_TRUE(fe_it) << "Iterator invalid in FaceEdgeIter at step 1";
  --fe_it;
  EXPECT_EQ(3, fe_it->idx() ) << "Index wrong in FaceEdgeIter at step 2";
  EXPECT_TRUE(fe_it) << "Iterator invalid in FaceEdgeIter at step 2";
  --fe_it;
  EXPECT_EQ(4, fe_it->idx() ) << "Index wrong in FaceEdgeIter at end";
  EXPECT_FALSE(fe_it) << "Iterator invalid in FaceEdgeIter at end";
  EXPECT_TRUE( fe_it == fe_end )  << "End iterator for FaceEdgeIter not matching";

  Mesh::ConstFaceEdgeIter cfe_it  = mesh_.cfe_begin(mesh_.face_handle(1));
  Mesh::ConstFaceEdgeIter cfe_end = mesh_.cfe_end(mesh_.face_handle(1));

  EXPECT_EQ(4, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at initialization";
  EXPECT_TRUE(cfe_it) << "Iterator invalid in ConstFaceEdgeIter at initialization";
  --cfe_it;
  EXPECT_EQ(1, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at step 1";
  EXPECT_TRUE(cfe_it) << "Iterator invalid in ConstFaceEdgeIter at step 1";
  --cfe_it;
  EXPECT_EQ(3, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at step 2";
  EXPECT_TRUE(cfe_it) << "Iterator invalid in ConstFaceEdgeIter at step 2";
  --cfe_it;
  EXPECT_EQ(4, cfe_it->idx() ) << "Index wrong in ConstFaceEdgeIter at end";
  EXPECT_FALSE(cfe_it) << "Iterator invalid in ConstFaceEdgeIter at end";
  EXPECT_TRUE( cfe_it == cfe_end )  << "End iterator for ConstFaceEdgeIter not matching";

}
*/
