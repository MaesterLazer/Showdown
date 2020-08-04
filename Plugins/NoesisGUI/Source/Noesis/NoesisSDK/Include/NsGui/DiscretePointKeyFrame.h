////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DISCRETEPOINTKEYFRAME_H__
#define __GUI_DISCRETEPOINTKEYFRAME_H__


#include <NsCore/Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/PointKeyFrame.h>
#include <NsGui/AnimationApi.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Animates from the *Point* value of the previous key frame to its own *Value* using discrete
/// interpolation.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.discretepointkeyframe.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API DiscretePointKeyFrame final: public PointKeyFrame
{
public:
    // Hides Freezable methods for convenience
    //@{
    Ptr<DiscretePointKeyFrame> Clone() const;
    Ptr<DiscretePointKeyFrame> CloneCurrentValue() const;
    //@}

protected:
    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    //@}

    /// From KeyFrame
    //@{
    Point InterpolateValueCore(const Point& baseValue, float keyFrameProgress) override;
    //@}

    NS_DECLARE_REFLECTION(DiscretePointKeyFrame, PointKeyFrame)
};

}


#endif
