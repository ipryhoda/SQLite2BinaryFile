#include "SQLiteCommandLine.h"
#include <utility>
#include <cassert>

bool IsOption(const std::string& strArg)
{
    if ((strArg[0] == L'/') || (strArg[0] != L'-'))
        return true;
    return false;
}

enum EWaitingFor
{
    waitforActionSwitch
    , waitforActionType
    , waitforActionSpecificParams
    //, waitfor
};


enum EActionType
{
    acttypNone
    , acttypSerialize
    , acttypVerify
    //, acttyp
};

struct TSerialization_Action
{
    enum EWaitingFor
    {
        waitforSwitch

        , waitforXmlFile
        , waitforSaveset
    };
};

struct TVerification_Action
{
    enum EWaitingFor
    {
        waitforSwitch

        , waitforSaveset
        , waitforShow
    };
};

union UActionParams
{
    TSerialization_Action::EWaitingFor waitforSerialization;
    TVerification_Action::EWaitingFor waitforVerificaiton;

    //NXxx_Action::EWaitingFor waitforXxx;
};

CSQLiteCommandLine::CSQLiteCommandLine(const std::vector<std::string>& vecOptions) : m_vecOptions(vecOptions)
{}

void CSQLiteCommandLine::Parse()
{
    EWaitingFor eWaitingFor = waitforActionSwitch;
    EActionType eActionToDo = acttypNone;

    UActionParams actparams;
    memset(&actparams, 0, sizeof(actparams));
    for (auto& it : m_vecOptions)
    {
        switch (eWaitingFor)
        {
        case(waitforActionSwitch):
        {
            if (IsOption(it) && it.compare("a") == 0)
            {
                eWaitingFor = waitforActionType;
            }
            break;
        }

        case(waitforActionType):
        {
            if (IsOption(it) && it.compare("a") == 0)
            {
                if (it.compare(STR_SERIALIZE) == 0)
                {
                    actparams.waitforSerialization = TSerialization_Action::waitforSwitch;
                    eActionToDo = acttypSerialize;
                }
                if (it.compare(STR_VERIFY) == 0)
                {
                    actparams.waitforVerificaiton = TVerification_Action::waitforSwitch;
                    eActionToDo = acttypVerify;
                }
                else
                {
                    throw command_line_parse_error("Invalid operation type");
                }

                m_handled.emplace(std::make_pair(STR_ACTION, it));
                eWaitingFor = waitforActionSpecificParams;
            }
            break;
        }
        case(waitforActionSpecificParams):
        {
            switch (eActionToDo)
            {
            case(acttypSerialize):
            {
                switch (actparams.waitforSerialization)
                {
                case(TSerialization_Action::waitforSwitch):
                {
                    if (IsOption(it))
                    {
                        if (it.compare(STR_XML_FILE) == 0)
                        {
                            actparams.waitforSerialization = TSerialization_Action::waitforXmlFile;
                        }
                        else if (it.compare(STR_SAVESET) == 0)
                        {
                            actparams.waitforSerialization = TSerialization_Action::waitforSaveset;
                        }
                        else
                        {
                            throw command_line_parse_error("Invalid option for serialization");
                        }
                    }
                    else
                    {
                        m_handled.emplace(std::make_pair(STR_SOURCE, it));
                    }

                    break;
                }
                case(TSerialization_Action::waitforXmlFile):
                {
                    if (!IsOption(it))
                    {
                        m_handled.emplace(std::make_pair(STR_XML_FILE, it));
                    }
                    else
                    {
                        throw command_line_parse_error("Invalid value for xml file. Seems to be the option name");
                    }

                    actparams.waitforSerialization = TSerialization_Action::waitforSwitch;
                    break;
                }
                case(TSerialization_Action::waitforSaveset):
                {
                    if (!IsOption(it))
                    {
                        m_handled.emplace(std::make_pair(STR_SAVESET, it));
                    }
                    else
                    {
                        throw command_line_parse_error("Invalid value for saveset file. Seems to be the option name");
                    }

                    actparams.waitforSerialization = TSerialization_Action::waitforSwitch;
                    break;
                }
                default:
                    assert(0);
                }
            
                break;
            }
            case(acttypVerify):
            {
                switch (actparams.waitforVerificaiton)
                {
                case(TVerification_Action::waitforSwitch):
                {
                    if (IsOption(it))
                    {
                        if (it.compare(STR_SHOW) == 0)
                        {
                            actparams.waitforVerificaiton = TVerification_Action::waitforShow;
                        }
                        else if (it.compare(STR_SAVESET) == 0)
                        {
                            actparams.waitforVerificaiton = TVerification_Action::waitforSaveset;
                        }
                        else
                        {
                            throw command_line_parse_error("Invalid option for verifications");
                        }
                    }
                    else
                    {
                        throw command_line_parse_error("Invalid option is set for varification");
                    }

                    break;
                }
                case(TVerification_Action::waitforShow):
                {
                    if (!IsOption(it))
                    {
                        m_handled.emplace(std::make_pair(STR_SHOW, it));
                    }
                    else
                    {
                        throw command_line_parse_error("Invalid value for show row count. Seems to be the option name");
                    }

                    actparams.waitforVerificaiton = TVerification_Action::waitforSwitch;
                    break;
                }
                case(TVerification_Action::waitforSaveset):
                {
                    if (!IsOption(it))
                    {
                        m_handled.emplace(std::make_pair(STR_SAVESET, it));
                    }
                    else
                    {
                        throw command_line_parse_error("Invalid value for saveset file. Seems to be the option name");
                    }

                    actparams.waitforVerificaiton = TVerification_Action::waitforSwitch;
                    break;
                }
                default:
                    assert(0);
                }

                break;
            }
            default:
                assert(0);
            }
        }
        default:
            assert(0);
        }
    }
}

CSQLiteCommandLine::~CSQLiteCommandLine()
{}

std::string CSQLiteCommandLine::GetAction() const
{
    return m_handled.at(STR_ACTION);
}

std::string CSQLiteCommandLine::GetSaveset() const
{
    return m_handled.at(STR_SAVESET);
}

std::string CSQLiteCommandLine::GetSource() const
{
    return m_handled.at(STR_SOURCE);
}

std::string CSQLiteCommandLine::GetSchema() const
{
    std::string strXml = "./config/schema.xml";
    if (m_handled.find(STR_XML_FILE) != m_handled.end())
    {
        strXml = m_handled.at(STR_XML_FILE);
    }

    return strXml;
}

size_t CSQLiteCommandLine::GetShowCount() const
{
    size_t uiCount = -1;
    if (m_handled.find(STR_SHOW) != m_handled.end())
    {
        char * pEnd = nullptr;
        uiCount = std::strtoull(m_handled.at(STR_SHOW).c_str(), &pEnd, 10);
    }

    return uiCount;
}

