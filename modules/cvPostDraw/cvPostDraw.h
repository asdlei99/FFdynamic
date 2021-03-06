#pragma once

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "davWave.h"
#include "davImpl.h"
#include "cvPeerDynaEvent.h"

namespace ff_dynamic {

/* create CvPostDraw class category */
struct DavWaveClassCvPostDraw : public DavWaveClassCategory {
    DavWaveClassCvPostDraw () :
        DavWaveClassCategory(type_index(typeid(*this)), type_index(typeid(std::string)), "CvPostDraw") {}
};

/* options passing use AVDictionary */
class CvPostDraw : public DavImpl {
public:
    CvPostDraw(const DavWaveOption & options) : DavImpl(options) {
        implDefaultInstantiate();
    }
    virtual ~CvPostDraw() {onDestruct();}

private:
    CvPostDraw(const CvPostDraw &) = delete;
    CvPostDraw & operator= (const CvPostDraw &) = delete;
    virtual int onConstruct();
    virtual int onDestruct();
    virtual int onProcess(DavProcCtx & ctx);
    virtual int onProcessTravelDynamic(DavProcCtx & ctx) {return 0;}
    virtual int onDynamicallyInitializeViaTravelStatic(DavProcCtx & ctx);
    virtual const DavRegisterProperties & getRegisterProperties() const noexcept;

private: // event process
    int processDnnDetectResult(const CvDnnDetectEvent & e);
    int processStopPubEvent(const DavStopPubEvent & e);

private:
    map<DavProcFrom, vector<CvDnnDetectEvent>> m_detectResults;
    vector<shared_ptr<DavProcBuf>> m_cacheBufFrames;
    int drawResult(cv::Mat & image, const vector<CvDnnDetectEvent> & results);
};

} //namespace ff_dynamic
