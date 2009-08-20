#include "stdafx.h"
#include "controlanalogencoder.h"

ControlAnalogEncoder::ControlAnalogEncoder(void)
{
}

ControlAnalogEncoder::~ControlAnalogEncoder(void)
{
}

bool ControlAnalogEncoder::Load( const QDomElement &elem, QString *sError )
{
    if ( !GetPort( elem, "PortA", m_nPortA, sError ) )
	return false;
    if ( !GetPort( elem, "PortB", m_nPortB, sError ) )
	return false;
    if ( !XMLUtility::getAttributeBool( elem, "PullupA", m_bPullupA, sError ) )
	return false;
    if ( !XMLUtility::getAttributeBool( elem, "PullupB", m_bPullupB, sError ) )
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


ByteArray ControlAnalogEncoder::GetHIDReportDescriptor( StringTable &table, int &nBits ) const
{
    HIDReportDescriptorBuilder Desc;

    Desc.UsagePage(m_nUsagePage);
    Desc.Usage(m_nUsage);
    Desc.LogicalMinimum(0);
    Desc.LogicalMaximum(255);
    Desc.ReportSize(8);
    Desc.ReportCount(1);
    nBits += 8;
    if ( !m_sName.isEmpty() )
        Desc.StringIndex(table[m_sName]);
    Desc.Input(EDataType::Data, EVarType::Variable, ERelType::Relative, EWrapType::Wrap, ELinearType::Linear, EPreferedType::NoPreferred, ENullPositionType::NoNullPosition, EBufferType::BitField);

    return Desc;
}

        // returns the micro controller application data
ByteArray ControlAnalogEncoder::GetControlConfig( byte nReportId ) const
{
    struct SAnalogEncoderControl config;
    memset( &config, 0, sizeof(config) );

    config.hdr.Type = AnalogEncoder;
    config.hdr.ReportId = nReportId;
    config.hdr.Length = sizeof(config);
    config.PortA = (byte)m_nPortA;
    config.PortB = (byte)m_nPortB;
    config.Options = (m_bDebounce ? (1<<AE_DEBOUNCE) : 0 ) |
		     (m_bPullupA ? (1<<AE_PULLUPA) : 0 ) |
		     (m_bPullupB ? (1<<AE_PULLUPB) : 0 );
    return ByteBuffer((byte *)&config, sizeof(config) );
}