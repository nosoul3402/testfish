//
//  Order.h
//  FishX
//
//  Created by peng on 13-7-22.
//
//

#import <UIKit/UIKit.h>

@interface Order : NSObject{
    NSString        *_cooOrderSerial;
    NSString        *_billingIndex;
}

@property(nonatomic,retain) NSString        *_cooOrderSerial;
@property(nonatomic,retain) NSString        *_billingIndex;

@end
