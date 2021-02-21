#pragma once

#include "IHardwareInfoMonitoring.h"
#include "CDrivesInfoJSONDatabase.h"

class CContainerOfLogicalDisk;
class CHardwareStatusSpecification;
class CJSONFormatterLogicalDisk;

class CLogicalDiskInfoMonitoring :
    public IHardwareInfoMonitoring
{
public:
    CLogicalDiskInfoMonitoring( ) = delete;
    /// <summary>
    /// Saving specification of LogicalDisk information
    /// </summary>
    /// <param name="specification"> must be in dynamic memory </param>
    explicit CLogicalDiskInfoMonitoring(
        CEvent& stop_event,
        CHardwareStatusSpecification* specification,
        std::shared_ptr<CDrivesInfoJSONDatabase> p_database);

    explicit CLogicalDiskInfoMonitoring(
        CHardwareStatusSpecification* specification,
        CContainerOfLogicalDisk* container_in_lifecircle,
        CEvent& stop_event,
        std::shared_ptr<CDrivesInfoJSONDatabase> p_database);

    CLogicalDiskInfoMonitoring(CLogicalDiskInfoMonitoring&)
        = delete;
    CLogicalDiskInfoMonitoring(CLogicalDiskInfoMonitoring&&)
        noexcept = delete;

    ~CLogicalDiskInfoMonitoring( );
    /// <summary>
    /// infinite loop. Stoped only if stop-event
    /// </summary>
    virtual bool StartMonitoringInfo( ) override;

private:
    std::shared_ptr<CDrivesInfoJSONDatabase> m_p_database;
    CHardwareStatusSpecification* m_p_specification;
    CContainerOfLogicalDisk* m_p_container;
};

