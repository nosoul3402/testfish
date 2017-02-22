//
//  Order.m
//  FishX
//
//  Created by peng on 13-7-22.
//
//

#import "Order.h"

@implementation Order

@synthesize _cooOrderSerial;
@synthesize _billingIndex;


- (void)encodeWithCoder:(NSCoder *)aCoder
{
    [aCoder encodeObject:self._cooOrderSerial forKey:@"name"];
    [aCoder encodeObject:self._billingIndex forKey:@"index"];
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super init];
   if (self) {
       self._cooOrderSerial = [aDecoder decodeObjectForKey:@"name"];
       self._billingIndex = [aDecoder decodeObjectForKey:@"index"];
    }
    return self;
}

- (void)dealloc{
    [_billingIndex release];
    [_cooOrderSerial release];
    [super dealloc];
    
}

@end
