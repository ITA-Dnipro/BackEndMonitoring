#pragma once

#include "HardwareInfoLifeCycle.h"
#include "ContainerOfLogicalDisk.h"


class LogicalDiskStatusLifeCycle :
    public HardwareInfoLifeCycle
{
public:
    LogicalDiskStatusLifeCycle() = delete;
    /// <summary>
    /// Saving specification of LogicalDisk information
    /// </summary>
    /// <param name="specification"> must be in dynamic memory </param>
    LogicalDiskStatusLifeCycle(HardwareStatusSpecification* specification)
        : specification_(specification)
    { };
    LogicalDiskStatusLifeCycle(HardwareStatusSpecification* specification, 
        ContainerOfLogicalDisk* container_in_lifecircle) : 
        specification_(specification), 
        container_in_lifecircle_(container_in_lifecircle)
    { };
    LogicalDiskStatusLifeCycle(LogicalDiskStatusLifeCycle& orig) :
        specification_(orig.specification_),
        container_in_lifecircle_(orig.container_in_lifecircle_)
    { };
    LogicalDiskStatusLifeCycle(LogicalDiskStatusLifeCycle&&) noexcept = delete;

    ~LogicalDiskStatusLifeCycle()
    {
        delete specification_;
        delete container_in_lifecircle_;
    }
    /// <summary>
    /// infinite loop. Stoped only if stop-event
    /// </summary>
    virtual void ThreadLifeCycle() override;

private:
    HardwareStatusSpecification* specification_ = nullptr;
    ContainerOfLogicalDisk* container_in_lifecircle_ = nullptr;
};

