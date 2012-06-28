//
//  Shader.fsh
//  TestApp
//
//  Created by Alexander Alimov on 6/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
