#include "stdafx.h"
#include "controlswitch.h"

ControlSwitch::ControlSwitch(void)
{
}

ControlSwitch::~ControlSwitch(void)
{
}


bool ControlSwitch::Load( const QDomElement &elem, QString *sError )
{
    if ( !GetPort( elem, "Port", m_nPort, sError ) )
	return false;
    if ( !XMLUtility::getAttributeBool( elem, "Pullup", m_bPullup, sError ) )
	return false;
    if ( !XMLUtility::getAttributeBool( elem, "Debounce", m_bDebounce, sError ) )
	return false;
    if ( !XMLUtility::getAttributeString( elem, "Name", m_sName, sError ) )
	return false;
    if ( !XMLUtility::getAttributeUShort( elem, "UsagePage", m_nUsagePage, 0, 0xFFFF, sError ) )
	return false;
    if ( !XMLUtility::getAttributeUShort( elem, "Usage", m_nUsage, 0, 0xFFFF, sError ) )
	return false;
    return true;
}


ByteArray ControlSwitch::GetHIDReportDescriptor( StringTable &table, int &nBits ) const
{
    HIDReportDescriptorBuilder Desc;

    Desc.UsagePage(m_nUsagePage);
    Desc.Usage(m_nUsage);
    Desc.LogicalMinimum(0);
    Desc.LogicalMaximum(1);
    Desc.ReportSize(1);
    Desc.ReportCount(1);
    nBits++;
    if ( !m_sName.isEmpty() )
        Desc.StringIndex(table[m_sName]);
    Desc.Input(EDataType::Data, EVarType::Variable, ERelType::Absolute, EWrapType::NoWrap, ELinearType::Linear, EPreferedType::NoPreferred, ENullPositionType::NoNullPosition, EBufferType::BitField);

    return Desc;
}

        // returns the micro controller application data
ByteArray ControlSwitch::GetControlConfig( byte nReportId ) const
{
    struct SSwitchControl config;
    memset( &config, 0, sizeof(config) );

    config.hdr.Type = Switch;
    config.hdr.ReportId = nReportId;
    config.hdr.Length = sizeof(config);
    config.Port = (byte)m_nPort;
    config.Options = (m_bDebounce ? (1<<SW_DEBOUNCE) : 0 ) |
		     (m_bPullup ? (1<<SW_PULLUP) : 0 );
    config.Debounce = 0;

    return ByteBuffer((byte *)&config, sizeof(config) );
}