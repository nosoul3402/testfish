//
//  CCLagrangeConfig.h
//  FishX
//
//  Created by peng on 13-1-25.
//
//

#ifndef FishX_CCLagrangeConfig_h
#define FishX_CCLagrangeConfig_h

#ifdef __cplusplus

USING_NS_CC;

typedef struct CCLagrangeConfig {
	// cubic or quadratic
	bool cubic;
    
	// start and end
	float startX, startY, endX, endY;
    
	// control point
	float cp1X, cp1Y, cp2X, cp2Y;
    
	// knot
	float t0, t1, t2, t3;
} ccLagrangeConfig;

extern "C" {
#endif
    
    /**
     * 创建一个二次拉格朗日曲线配置
     *
     * @param startX 起始点x位置
     * @param startY 起始点y位置
     * @param endX 结束点x位置
     * @param endY 结束点y位置
     * @param cp1X 控制点x位置
     * @param cp1Y 控制点y位置
     * @return \link wyLagrangeConfig wyLagrangeConfig\endlink
     */
    static inline ccLagrangeConfig wylcQuad(float startX, float startY, float endX, float endY, float cp1X, float cp1Y) {
        ccLagrangeConfig c = {
            false,
            startX, startY, endX, endY,
            cp1X, cp1Y, 0, 0,
            0, 0.5f, 1.0f, 0
        };
        return c;
    }
    
    /**
     * 创建一个三次拉格朗日曲线配置
     *
     * @param startX 起始点x位置
     * @param startY 起始点y位置
     * @param endX 结束点x位置
     * @param endY 结束点y位置
     * @param cp1X 第一控制点x位置
     * @param cp1Y 第一控制点y位置
     * @param cp2X 第二控制点x位置
     * @param cp2Y 第二控制点y位置
     * @return \link wyLagrangeConfig wyLagrangeConfig\endlink
     */
    static inline ccLagrangeConfig wylcCubic(float startX, float startY, float endX, float endY, float cp1X, float cp1Y, float cp2X, float cp2Y) {
        ccLagrangeConfig c = {
            true,
            startX, startY, endX, endY,
            cp1X, cp1Y, cp2X, cp2Y,
            0, 0.33333f, 0.66666f, 1.0f
        };
        return c;
    }
    
    /**
     * 给定一个t值，区间0到1，计算拉格朗日曲线在t位置的坐标
     *
     * @param c \link wyLagrangeConfig wyLagrangeConfig\endlink
     * @param t 取样值，从0到1
     * @return 计算出来的点坐标
     */
    static CCPoint wylcPointAt(ccLagrangeConfig & c, float t) {
        cocos2d::CCPoint v;
        
        if(c.cubic) {
            float ti[] = { c.t0, c.t1, c.t2, c.t3 };
            float bF[4];
            for(int j = 0; j < 4; j++) {
                float P = 1;
                for(int i = 0; i < 4; i++) {
                    if(i != j)
                        P = P * (t - ti[i]) / (ti[j] - ti[i]);
                }
                bF[j] = P;
            }
            
            CCPoint start = ccp(c.startX, c.startY);
            start = ccpMult(start, bF[0]);
            CCPoint cp1 = ccp(c.cp1X, c.cp1Y);
            cp1 = ccpMult(cp1, bF[1]);
            CCPoint cp2 = ccp(c.cp2X, c.cp2Y);
            cp2 = ccpMult(cp2, bF[2]);
            CCPoint end = ccp(c.endX, c.endY);
            end = ccpMult(end, bF[3]);
            v = ccpAdd(ccpAdd(ccpAdd(start, cp1), cp2), end);
        } else {
            float ti[] = { c.t0, c.t1, c.t2 };
            float bF[3];
            for(int j = 0; j < 3; j++) {
                float P = 1;
                for(int i = 0; i < 3; i++) {
                    if(i != j)
                        P = P * (t - ti[i]) / (ti[j] - ti[i]);
                }
                bF[j] = P;
            }
            
            CCPoint start = ccp(c.startX, c.startY);
            start = ccpMult(start, bF[0]);
            CCPoint cp1 = ccp(c.cp1X, c.cp1Y);
            cp1 = ccpMult(cp1, bF[1]);
            CCPoint end = ccp(c.endX, c.endY);
            end = ccpMult(end, bF[2]);
            v = ccpAdd(ccpAdd(start, cp1), end);
        }
        
        return v;
    }
    
#ifdef __cplusplus
}
#endif

#endif
