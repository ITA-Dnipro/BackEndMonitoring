#pragma once

#include "CHardwareInfoLifeCycle.h"
#include "ÑContainerOfLogicalDisk.h"


class CLogicalDiskStatusLifeCycle :
    public CHardwareInfoLifeCycle
{
public:
    CLogicalDiskStatusLifeCycle() = delete;
    /// <summary>
    /// Saving specification of LogicalDisk information
    /// </summary>
    /// <param name="specification"> must be in dynamic memory </param>
    explicit CLogicalDiskStatusLifeCycle(
        ÑHardwareStatusSpecification* specification) : 
        m_specification(specification)
    { };
    explicit CLogicalDiskStatusLifeCycle(
        ÑHardwareStatusSpecification* specification,
        ÑContainerOfLogicalDisk* container_in_lifecircle) : 
        m_specification(specification), 
        m_container_in_lifecircle(container_in_lifecircle)
    { };
    explicit CLogicalDiskStatusLifeCycle(
        const CLogicalDiskStatusLifeCycle& orig) :
        m_specification(orig.m_specification),
        m_container_in_lifecircle(orig.m_container_in_lifecircle)
    { };
    CLogicalDiskStatusLifeCycle(CLogicalDiskStatusLifeCycle&&) 
        noexcept = delete;

    ~CLogicalDiskStatusLifeCycle()
    {
        delete m_specification;
        delete m_container_in_lifecircle;
    }
    /// <summary>
    /// infinite loop. Stoped only if stop-event
    /// </summary>
    virtual void ThreadLifeCycle() override;

private:
    ÑHardwareStatusSpecification* m_specification = nullptr;
    ÑContainerOfLogicalDisk* m_container_in_lifecircle = nullptr;
};

