/*
 *  PlanetCube.h
 *  NFSpace
 *
 *  Created by Steven Wittens on 9/08/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PlanetCube_H
#define PlanetCube_H

class PlanetCube;

#include <Ogre/Ogre.h>

#include "Planet.h"
#include "PlanetCubeTree.h"

#include "PlanetMap.h"

using namespace Ogre;

namespace NFSpace {

/**
 * Data structure for loading and storing the cube-based tesselation of a planet surface.
 */
class PlanetCube {
    friend class PlanetRenderable;

public:
    /**
     * Constructor
     */
    PlanetCube(MovableObject* proxy, PlanetMap* map);
    ~PlanetCube();

    static const Matrix3 getFaceTransform(int face, bool lhs);
        
    const Real getScale() const;
    virtual void updateRenderQueue(RenderQueue* queue, const Matrix4& fullTransform);
    void setCamera(Camera* camera);
    
    
protected:
    void initQuadTreeNode(QuadTreeNode* node);
    void initFace(int face);
    void deleteFace(int face);
    
    QuadTree* mFaces[6];
    MovableObject* mProxy;
    PlanetMap* mMap;
    
    SimpleFrustum mLODFrustum;
    Camera* mLODCamera;
    Vector3 mLODPosition;
    Real mLODPixelFactor;
    Vector3 mLODCameraPlane;
    Real mLODSphereClip;
};

};

#endif