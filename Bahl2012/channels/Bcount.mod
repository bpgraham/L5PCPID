: Burst counter
: Counts a burst if current ISI<bisi and previous ISI>bisi
: bisi might typically be set to around 20ms
: Adapted from APCount
: BPG 5-9-22

NEURON {
	POINT_PROCESS BCount
	RANGE nap, thresh, time, firing, bisi, nb, cisi, pisi, ptime
}

UNITS {
	(mV) = (millivolt)
}

PARAMETER {
	nap
	nb
	thresh = -20 (mV)
	bisi = 20 (ms)
	time (ms)
}

ASSIGNED {
	firing
	space
	ptime
	cisi
	pisi
}

INITIAL {
	nap = 0
	nb = 0
	firing = 0
	time = -1000
	ptime = -1000
	cisi = 1000
	pisi = 1000
	check()
}

BREAKPOINT {
	SOLVE check METHOD after_cvode
}

PROCEDURE check() {
VERBATIM
	if (v >= thresh && !firing) {
		firing = 1;
		ptime = time;
		time = t;
		nap += 1.;
		pisi = cisi;
		cisi = time - ptime;
		if (cisi <= bisi && pisi > bisi) {
			nb += 1.;
		}
	}
	if (firing && v < thresh && t > time) {
		firing = 0;
	}
ENDVERBATIM
}


