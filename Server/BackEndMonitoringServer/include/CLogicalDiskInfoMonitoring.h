#pragma once

#include "IHardwareInfoMonitoring.h"

class CContainerOfLogicalDisk;
class CHardwareStatusSpecification;
class CJSONFormatterLogicalDisk;

class CLogicalDiskInfoMonitoring :
    public IHardwareInfoMonitoring
{
public:
    CLogicalDiskInfoMonitoring() = delete;
    /// <summary>
    /// Saving specification of LogicalDisk information
    /// </summary>
    /// <param name="specification"> must be in dynamic memory </param>
    explicit CLogicalDiskInfoMonitoring(
        CEvent& stop_event,
        CHardwareStatusSpecification* specification,
        CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter);

    explicit CLogicalDiskInfoMonitoring(
        CHardwareStatusSpecification* specification,
        CContainerOfLogicalDisk* container_in_lifecircle,
        CEvent& stop_event,
        CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter);

    CLogicalDiskInfoMonitoring(CLogicalDiskInfoMonitoring&)
        = delete;
    CLogicalDiskInfoMonitoring(CLogicalDiskInfoMonitoring&&) 
        noexcept = delete;

    ~CLogicalDiskInfoMonitoring();
    /// <summary>
    /// infinite loop. Stoped only if stop-event
    /// </summary>
    virtual bool StartMonitoringInfo() override;

private:
    CHardwareStatusSpecification* m_p_specification;
    CContainerOfLogicalDisk* m_p_container;
    CThreadSafeVariable<CJSONFormatterLogicalDisk>& m_json_formatter;
};

