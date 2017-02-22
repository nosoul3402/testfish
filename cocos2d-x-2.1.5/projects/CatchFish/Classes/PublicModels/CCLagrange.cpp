//
//  CCLagrange.cpp
//  FishX
//
//  Created by peng on 13-1-25.
//
//

#include "CCLagrange.h"

/*
 * Copyright (c) 2010 WiYun Inc.
 * Author: luma(stubma@gmail.com)
 *
 * For all entities this program is free software; you can redistribute
 * it and/or modify it under the terms of the 'WiEngine' license with
 * the additional provision that 'WiEngine' must be credited in a manner
 * that can be be observed by end users, for example, in the credits or during
 * start up. (please find WiEngine logo in sdk's logo folder)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
//#include "CCNode.h"

CCLagrange::CCLagrange(){
	
}

CCLagrange::CCLagrange(float duration, ccLagrangeConfig config) :
    /*CCActionInterval::actionWithDuration(duration),*/
    m_config(config),
    m_pinPoint(ccp(MAXFLOAT, MAXFLOAT)),
    m_pinDelta(0),
    m_autoRotate(false),
    m_angleDelta(0) {
}

CCLagrange::~CCLagrange() {
}

CCLagrange* CCLagrange::create(float duration, ccLagrangeConfig config) {
	CCLagrange* lagrange = new CCLagrange(duration, config);
    lagrange->initWithDuration(duration);
    lagrange->autorelease();
	return lagrange;
}

bool CCLagrange::initWithDuration(float t)
{
	if (CCActionInterval::initWithDuration(t))
	{
		return true;
	}
    
	return false;
}

/*
CCLagrange* CCLagrange::copy() {
	CCLagrange* l = CCLagrange::make(m_fDuration, m_config);
	l->setAutoRotate(m_autoRotate, m_angleDelta);
	l->setPinAngleDelta(m_pinDelta);
	l->setPinPoint(m_pinPoint);
	return l;
}
 */
/*
CCAction* CCLagrange::reverse() {
	// copy config
	wyLagrangeConfig r;
	memcpy(&r, &m_config, sizeof(wyLagrangeConfig));
    
	// reverse points
	float tmp = r.startX;
	r.startX = r.endX;
	r.endX = tmp;
	tmp = r.startY;
	r.startY = r.endY;
	r.endY = tmp;
	if(r.cubic) {
		tmp = r.cp1X;
		r.cp1X = r.cp2X;
		r.cp2X = tmp;
		tmp = r.cp1Y;
		r.cp1Y = r.cp2Y;
		r.cp2Y = tmp;
        
		tmp = r.t0;
		r.t0 = 1 - r.t3;
		r.t3 = 1 - tmp;
		tmp = r.t1;
		r.t1 = 1 - r.t2;
		r.t2 = 1 - tmp;
	} else {
		tmp = r.t2;
		r.t2 = 1 - r.t0;
		r.t0 = 1 - tmp;
	}
    
	wyLagrange* l = wyLagrange::make(m_duration, r);
	l->setAutoRotate(m_autoRotate, 180 - m_angleDelta);
	l->setPinAngleDelta(m_pinDelta);
	l->setPinPoint(m_pinPoint);
	return l;
}
*/

/**
 * 计算得到向量方向的弧度
 *
 * @param v 向量
 * @return 向量方向的弧度，返回值范围在[-pi, pi]
 */
static inline float wypToRadian(CCPoint v) {
	return atan2(v.y, v.x);
}


static float r2d(float radian) {
	return (radian / M_PI * 180.0f);
}
/**
 * 计算得到向量方向的角度
 *
 * @param v 向量
 * @return 向量方向的角度，返回值范围在[-180, 180]
 */
static inline float wypToDegree(CCPoint v) {
	return r2d(wypToRadian(v));
}

void CCLagrange::update(float t) {
	CCPoint p = wylcPointAt(m_config, t);
	m_pTarget->setPosition(p.x, p.y);
    
	// check direction
	if(m_autoRotate) {
		CCPoint p2 = wylcPointAt(m_config, t + 0.016f);
		CCPoint d = ccpSub(p2, p);
		float angle = - wypToDegree(d);
		angle += m_angleDelta;
		m_pTarget->setRotation(angle);
	} else if(m_pinPoint.x != MAXFLOAT && m_pinPoint.y != MAXFLOAT) {
		CCPoint anchor = ccp(m_pTarget->getAnchorPoint().x, m_pTarget->getAnchorPoint().y);
		anchor = m_pTarget->convertToWorldSpace(anchor);
		float angle = wypToDegree(ccpSub(m_pinPoint, anchor));
		m_pTarget->setRotation(-angle + m_pinDelta);
	}
    
	// super only call callback
	CCActionInterval::update(t);
}

void CCLagrange::setAutoRotate(bool flag, float angleDelta) {
	m_autoRotate = flag;
	m_angleDelta = angleDelta;
}
