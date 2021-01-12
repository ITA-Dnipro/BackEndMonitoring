#pragma once

#include "CHardwareInfoLifeCycle.h"
#include "�ContainerOfLogicalDisk.h"


class CLogicalDiskStatusLifeCycle :
    public CHardwareInfoLifeCycle
{
public:
    CLogicalDiskStatusLifeCycle() = delete;
    /// <summary>
    /// Saving specification of LogicalDisk information
    /// </summary>
    /// <param name="specification"> must be in dynamic memory </param>
    explicit CLogicalDiskStatusLifeCycle(CEvent& stop_event,
        �HardwareStatusSpecification* specification) : 
        CHardwareInfoLifeCycle(stop_event), m_p_specification(specification)
    { };
    explicit CLogicalDiskStatusLifeCycle(
        �HardwareStatusSpecification* specification,
        �ContainerOfLogicalDisk* container_in_lifecircle,
        CEvent& stop_event) : 
        m_p_specification(specification), 
        m_p_container_in_lifecircle(container_in_lifecircle),
        CHardwareInfoLifeCycle(stop_event)
    { };
    explicit CLogicalDiskStatusLifeCycle(CLogicalDiskStatusLifeCycle&)
        = delete;
    CLogicalDiskStatusLifeCycle(CLogicalDiskStatusLifeCycle&&) 
        noexcept = delete;

    ~CLogicalDiskStatusLifeCycle()
    {
        delete m_p_specification;
        delete m_p_container_in_lifecircle;
    }
    /// <summary>
    /// infinite loop. Stoped only if stop-event
    /// </summary>
    virtual void ThreadLifeCycle() override;

private:
    �HardwareStatusSpecification* m_p_specification = nullptr;
    �ContainerOfLogicalDisk* m_p_container_in_lifecircle = nullptr;
};

