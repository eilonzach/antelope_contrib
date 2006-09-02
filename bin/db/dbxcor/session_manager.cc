#include "session_manager.h"

using namespace std;
using namespace SEISPP;

SessionManager::SessionManager(string pfname, string hname, string lname, string wdbname, string rdbname)
{
    pf_name=pfname;
    event_file_name=hname;
    log_file_name=lname;
    waveform_db_name=wdbname;
    result_db_name=rdbname;

    parent=NULL;

    controls=new Widget[MAX_NUM_CONTROLS];
    sensitive=new bool[MAX_NUM_CONTROLS];
    for(int i=0; i<MAX_NUM_CONTROLS; i++) {
	sensitive[i]=false; //assume all buttons are diabled
	controls[i]=NULL;
    }
    log_stream=new ofstream(lname.c_str(), ios::out | ios::trunc);

    xpe=NULL;
    mcc=NULL;

    state=START;
    display_initial_sort_box=true;
    display_analysis_sort_box=true;
    evid=-1;
    orid=-1;
}

SessionManager::~SessionManager()
{
    delete controls;
    delete sensitive;
    delete log_stream;
 
    if (fp != NULL) fclose(fp);
    if (xpe != NULL) delete xpe;  //believe that deletion of xpe will result in deletion of the last mcc
}

void SessionManager::record( string s)
{
    XmTextInsert(msg_w,XmTextGetLastPosition(msg_w),(char *)(s.c_str()));
    (*log_stream) << s <<endl;
}

void SessionManager::session_state()
{
    switch(state) {
        case START:
	    state=NONE;
	    break;
	case NONE:
	    state=NEXT;
	    break;
        case NEXT:
	    state=REF;
	    break;
	case REF:
	    state=ANALYZE;
	    break;
	case ANALYZE:
	    state=NEXT;
    	    break;
	default:
	    break;
    }
    session_state(state);
}

void SessionManager::session_state(SessionState s)
{
    int i;

    state=s;

    // Whenever we enter this routine all gui items are first disabled
    // then we only turn on the one's appropriate for a given state
    for(int i=0; i<MAX_NUM_CONTROLS; i++) {
        sensitive[i]=false; 
    }

    switch (s) {
	case NONE: 
	    sensitive[BTN_NEXT]=true;    
	    sensitive[MENU_FILE]=true;
	    sensitive[MENU_FILE_EXIT]=true;
 	    sensitive[MENU_PICKS]=true;
 	    sensitive[MENU_OPTIONS]=true;
	    sensitive[MENU_SETTINGS]=true;
	    break;
	case NEXT:
	    sensitive[BTN_NEXT]=true;
	    sensitive[BTN_REF]=true;
	    sensitive[BTN_RESTORE]=true;
	    sensitive[MENU_FILE]=true;
            sensitive[MENU_FILE_EXIT]=true;
 	    sensitive[MENU_PICKS]=true;
	    sensitive[MENU_PICKS_BWIN]=true;
	    sensitive[MENU_PICKS_RWIN]=true;
	    sensitive[MENU_PICKS_TEDIT]=true;
	    sensitive[MENU_PICKS_CUTOFF]=true;
	    sensitive[MENU_PICKS_VIEW]=true;
  	    sensitive[MENU_PICKS_VIEW_ATTR]=true;
            sensitive[MENU_OPTIONS]=true;
	    sensitive[MENU_OPTIONS_SORT]=true;
            sensitive[MENU_OPTIONS_FILTER]=true;
            sensitive[MENU_SETTINGS]=true;
	    break;
	case REF:
            sensitive[BTN_NEXT]=true;
            sensitive[BTN_REF]=true;
            sensitive[BTN_ANALYZE]=true;
	    sensitive[BTN_RESTORE]=true;
            sensitive[MENU_FILE]=true;
            sensitive[MENU_FILE_EXIT]=true;
            sensitive[MENU_PICKS]=true;
            sensitive[MENU_PICKS_BWIN]=true;
            sensitive[MENU_PICKS_RWIN]=true;
            sensitive[MENU_PICKS_TEDIT]=true;
            sensitive[MENU_PICKS_CUTOFF]=true;
            sensitive[MENU_PICKS_VIEW]=true;
	    sensitive[MENU_PICKS_VIEW_ATTR]=true;
            sensitive[MENU_OPTIONS]=true;
            sensitive[MENU_OPTIONS_SORT]=true;
	    sensitive[MENU_OPTIONS_FILTER]=true;
            sensitive[MENU_SETTINGS]=true;
	    break;
	case ANALYZE:
            sensitive[BTN_NEXT]=true;
            sensitive[BTN_REF]=true;
            sensitive[BTN_ANALYZE]=true;
            sensitive[BTN_BEAM_PLOT]=true;
            sensitive[BTN_XCOR_PLOT]=true;
	    sensitive[BTN_RESTORE]=true;
            sensitive[MENU_FILE]=true;
            sensitive[MENU_FILE_EXIT]=true;
            sensitive[MENU_PICKS]=true;
            sensitive[MENU_PICKS_BWIN]=true;
            sensitive[MENU_PICKS_RWIN]=true;
            sensitive[MENU_PICKS_TEDIT]=true;
            sensitive[MENU_PICKS_CUTOFF]=true;
            sensitive[MENU_PICKS_VIEW]=true;
            sensitive[MENU_PICKS_VIEW_ATTR]=true;
 	    sensitive[MENU_OPTIONS]=true;
	    sensitive[MENU_OPTIONS_SORT]=true;
 	    sensitive[MENU_OPTIONS_FILTER]=true;
            sensitive[MENU_SETTINGS]=true;
	    break;
  	case SAVE:
            sensitive[BTN_NEXT]=true;
 	    sensitive[BTN_FILE_SAVE]=true;
            sensitive[BTN_REF]=true;
            sensitive[BTN_ANALYZE]=true;
            sensitive[BTN_BEAM_PLOT]=true;
            sensitive[BTN_XCOR_PLOT]=true;
	    sensitive[BTN_RESTORE]=true;
            sensitive[MENU_FILE]=true;
 	    sensitive[MENU_FILE_SAVE]=true;
            sensitive[MENU_FILE_EXIT]=true;
            sensitive[MENU_PICKS]=true;
            sensitive[MENU_PICKS_BWIN]=true;
            sensitive[MENU_PICKS_RWIN]=true;
            sensitive[MENU_PICKS_TEDIT]=true;
            sensitive[MENU_PICKS_CUTOFF]=true;
            sensitive[MENU_PICKS_VIEW]=true;
            sensitive[MENU_PICKS_VIEW_ATTR]=true;
            sensitive[MENU_OPTIONS]=true;
            sensitive[MENU_OPTIONS_SORT]=true;
            sensitive[MENU_OPTIONS_FILTER]=true;
            sensitive[MENU_SETTINGS]=true;
	    break;
	default:
	    break;
    }

    for(i=0; i<MAX_NUM_CONTROLS; i++) {
	if (controls[i]!=NULL) {
	    XtSetSensitive(controls[i],sensitive[i]);
	}
    }
}

bool SessionManager::validate_setting(stringstream & ss)
{
    string sort_order;
    int scase=0;

    switch (active_setting.result_sort_order) {
	case COHERENCE:
	    sort_order="coherence";
	    scase=1;
	    break;
	case CORRELATION_PEAK:
	    sort_order="peak correlation";
	    scase=1;
	    break;
	case AMPLITUDE:
	    sort_order="amplitude";
	    scase=1;
	    break;
	case LAG:
	    sort_order="lag";
	    scase=1;
	    break;
	case WEIGHT:
	    sort_order="stack weight";
	    scase=1;
	    break;
	case SITE_LAT:
	    sort_order="site.lat";
	    scase=0;
	    break;
	case SITE_LON:
	    sort_order="site.lon";
	    scase=0;
	    break;
	case PREDARR_TIME:
	    sort_order="predicted time";
	    scase=0;
	    break;
	default:
	    break;
    }

    if(scase==1 && state != ANALYZE && state != REF) {
	active_setting.result_sort_order=SITE_LAT;
	ss << "You specified an initial sort order of "<<sort_order<<endl<<
	    " which is not available before the analysis"<<endl<<
	    " of the ensemble, "
	    <<"the sort order is reset to "<<endl<<"site.lat"<<endl;
        if (display_initial_sort_box) return false;
    } else if (scase==0 && (state==ANALYZE || state==REF)) {
	active_setting.result_sort_order=COHERENCE;
	ss << "The sort order for the analysis result is set automatically "
	   << endl <<"to coherence from the specified "<<sort_order<<endl;
	if (display_analysis_sort_box) return false;
    }
 
    return true;
}
/* These are needed to deal with CSS3.0 database ids. */
void SessionManager::set_evid(int event_id)
{
	evid=event_id;;
}
void SessionManager::set_orid(int origin_id)
{
	orid=origin_id;;
}