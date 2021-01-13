#pragma once

#include "CHardwareInfoLifeCycle.h"
#include "�ContainerOfLogicalDisk.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CThreadSafeVariable.h"

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
        CEvent& stop_event,
        �HardwareStatusSpecification* specification,
        CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter) :
        CHardwareInfoLifeCycle(stop_event), 
        m_p_specification(specification),
        m_p_container_in_lifecircle(nullptr),
        m_json_formatter(json_formatter)
    { };

    explicit CLogicalDiskStatusLifeCycle(
        �HardwareStatusSpecification* specification,
        �ContainerOfLogicalDisk* container_in_lifecircle,
        CEvent& stop_event, 
        CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter) : 
        m_p_specification(specification), 
        m_p_container_in_lifecircle(container_in_lifecircle),
        CHardwareInfoLifeCycle(stop_event),
        m_json_formatter(json_formatter)
    { };

    CLogicalDiskStatusLifeCycle(CLogicalDiskStatusLifeCycle&)
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
    �HardwareStatusSpecification* m_p_specification;
    �ContainerOfLogicalDisk* m_p_container_in_lifecircle;
    CThreadSafeVariable<CJSONFormatterLogicalDisk>& m_json_formatter;
};

