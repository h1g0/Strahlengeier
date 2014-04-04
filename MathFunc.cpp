#include "MathFunc.h"
#include<cmath>
#define __USE_MYMATH
namespace MyMath{
#ifdef __USE_MYMATH
	//三角関係定数
	const unsigned short sin_table[] = {
		0,   804,  1608,  2412,  3216,  4019,  4821,  5623,
	 6424,  7223,  8022,  8820,  9616, 10411, 11204, 11996,
	12785, 13573, 14359, 15142, 15924, 16703, 17479, 18253,
	19024, 19792, 20557, 21319, 22078, 22834, 23586, 24334,
	25079, 25820, 26557, 27291, 28020, 28745, 29465, 30181,
	30893, 31600, 32302, 32999, 33692, 34379, 35061, 35738,
	36409, 37075, 37736, 38390, 39039, 39682, 40319, 40950,
	41575, 42194, 42806, 43411, 44011, 44603, 45189, 45768,
	46340, 46905, 47464, 48014, 48558, 49095, 49624, 50145,
	50659, 51166, 51664, 52155, 52638, 53113, 53580, 54039,
	54490, 54933, 55367, 55794, 56211, 56620, 57021, 57413,
	57797, 58171, 58537, 58895, 59243, 59582, 59913, 60234,
	60546, 60850, 61144, 61429, 61704, 61970, 62227, 62475,
	62713, 62942, 63161, 63371, 63571, 63762, 63943, 64114,
	64276, 64428, 64570, 64703, 64826, 64939, 65042, 65136,
	65219, 65293, 65357, 65412, 65456, 65491, 65515, 65530,
	65535, 0
	};

	double sin(double rad){
		long ix, subix, sign, tval;

		ix = (int)(rad * (I_PI / PI));   //単位変換
		sign = ix & I_PI;              //第3,第4象限である
		ix &= (I_PI - 1);              //第1,第2象限に限定
		if(ix > I_HPI) ix = I_PI - ix; //第1象限に限定

		subix = ix & (SUBINDEX - 1);   //線形補完に用いるサブインデックス
		ix >>= SUBBIT;                 //テーブル番号に変換

		//線形補完
		tval = ((long)sin_table[ix]   * (SUBINDEX - subix)
			  + (long)sin_table[ix+1] * subix);

		return (sign ? -tval : tval) / (SUBINDEX * 65535.0);
	}

	float sin(float rad){
		long ix, subix, sign, tval;

		ix = (int)(rad * (I_PI / PI));   //単位変換
		sign = ix & I_PI;              //第3,第4象限である
		ix &= (I_PI - 1);              //第1,第2象限に限定
		if(ix > I_HPI) ix = I_PI - ix; //第1象限に限定

		subix = ix & (SUBINDEX - 1);   //線形補完に用いるサブインデックス
		ix >>= SUBBIT;                 //テーブル番号に変換

		//線形補完
		tval = ((long)sin_table[ix]   * (SUBINDEX - subix)
			  + (long)sin_table[ix+1] * subix);

		return (sign ? -tval : tval) / (SUBINDEX * 65535.f);
	}

	double cos(double rad){
		return sin(rad+RIGHT_ANGLE);
	}
	float cos(float rad){
		return sin(rad+RIGHT_ANGLE_F);
	}

	const double atan_table[] = {
		0, 0.000977517, 0.00195503, 0.00293254, 0.00391005, 0.00488755, 0.00586504, 0.00684251,
		0.00781998, 0.00879743, 0.00977486, 0.0107523, 0.0117297, 0.012707, 0.0136844, 0.0146617,
		0.015639, 0.0166163, 0.0175935, 0.0185707, 0.0195479, 0.020525, 0.0215021, 0.0224791,
		0.0234561, 0.0244331, 0.02541, 0.0263868, 0.0273636, 0.0283404, 0.0293171, 0.0302938,
		0.0312704, 0.0322469, 0.0332234, 0.0341998, 0.0351761, 0.0361524, 0.0371286, 0.0381047,
		0.0390808, 0.0400568, 0.0410327, 0.0420085, 0.0429843, 0.0439599, 0.0449355, 0.045911,
		0.0468864, 0.0478618, 0.048837, 0.0498121, 0.0507872, 0.0517621, 0.052737, 0.0537117,
		0.0546864, 0.0556609, 0.0566354, 0.0576097, 0.0585839, 0.059558, 0.060532, 0.0615059,
		0.0624797, 0.0634533, 0.0644268, 0.0654002, 0.0663735, 0.0673467, 0.0683197, 0.0692926,
		0.0702654, 0.071238, 0.0722105, 0.0731829, 0.0741551, 0.0751272, 0.0760991, 0.0770709,
		0.0780425, 0.079014, 0.0799854, 0.0809566, 0.0819276, 0.0828985, 0.0838693, 0.0848398,
		0.0858103, 0.0867805, 0.0877506, 0.0887205, 0.0896903, 0.0906599, 0.0916293, 0.0925986,
		0.0935676, 0.0945365, 0.0955052, 0.0964738, 0.0974421, 0.0984103, 0.0993783, 0.100346,
		0.101314, 0.102281, 0.103248, 0.104215, 0.105182, 0.106149, 0.107115, 0.108082,
		0.109048, 0.110013, 0.110979, 0.111944, 0.11291, 0.113875, 0.11484, 0.115804,
		0.116768, 0.117733, 0.118696, 0.11966, 0.120624, 0.121587, 0.12255, 0.123513,
		0.124475, 0.125438, 0.1264, 0.127362, 0.128323, 0.129285, 0.130246, 0.131207,
		0.132167, 0.133128, 0.134088, 0.135048, 0.136008, 0.136967, 0.137926, 0.138885,
		0.139844, 0.140802, 0.14176, 0.142718, 0.143676, 0.144633, 0.14559, 0.146547,
		0.147503, 0.14846, 0.149416, 0.150371, 0.151327, 0.152282, 0.153237, 0.154192,
		0.155146, 0.1561, 0.157054, 0.158007, 0.15896, 0.159913, 0.160866, 0.161818,
		0.16277, 0.163722, 0.164673, 0.165624, 0.166575, 0.167525, 0.168476, 0.169426,
		0.170375, 0.171324, 0.172273, 0.173222, 0.17417, 0.175118, 0.176066, 0.177013,
		0.17796, 0.178907, 0.179853, 0.1808, 0.181745, 0.182691, 0.183636, 0.184581,
		0.185525, 0.186469, 0.187413, 0.188356, 0.189299, 0.190242, 0.191184, 0.192127,
		0.193068, 0.19401, 0.194951, 0.195891, 0.196832, 0.197771, 0.198711, 0.19965,
		0.200589, 0.201528, 0.202466, 0.203404, 0.204341, 0.205278, 0.206215, 0.207151,
		0.208087, 0.209023, 0.209958, 0.210893, 0.211828, 0.212762, 0.213695, 0.214629,
		0.215562, 0.216494, 0.217427, 0.218358, 0.21929, 0.220221, 0.221152, 0.222082,
		0.223012, 0.223941, 0.22487, 0.225799, 0.226727, 0.227655, 0.228583, 0.22951,
		0.230437, 0.231363, 0.232289, 0.233214, 0.23414, 0.235064, 0.235989, 0.236912,
		0.237836, 0.238759, 0.239682, 0.240604, 0.241526, 0.242447, 0.243368, 0.244289,
		0.245209, 0.246128, 0.247048, 0.247966, 0.248885, 0.249803, 0.25072, 0.251638,
		0.252554, 0.253471, 0.254386, 0.255302, 0.256217, 0.257131, 0.258045, 0.258959,
		0.259872, 0.260785, 0.261697, 0.262609, 0.26352, 0.264431, 0.265342, 0.266252,
		0.267162, 0.268071, 0.26898, 0.269888, 0.270796, 0.271703, 0.27261, 0.273516,
		0.274422, 0.275328, 0.276233, 0.277137, 0.278041, 0.278945, 0.279848, 0.280751,
		0.281653, 0.282555, 0.283456, 0.284357, 0.285257, 0.286157, 0.287057, 0.287956,
		0.288854, 0.289752, 0.290649, 0.291546, 0.292443, 0.293339, 0.294235, 0.29513,
		0.296024, 0.296918, 0.297812, 0.298705, 0.299598, 0.30049, 0.301381, 0.302272,
		0.303163, 0.304053, 0.304943, 0.305832, 0.306721, 0.307609, 0.308497, 0.309384,
		0.31027, 0.311156, 0.312042, 0.312927, 0.313812, 0.314696, 0.31558, 0.316463,
		0.317345, 0.318227, 0.319109, 0.31999, 0.320871, 0.321751, 0.32263, 0.323509,
		0.324388, 0.325265, 0.326143, 0.32702, 0.327896, 0.328772, 0.329647, 0.330522,
		0.331397, 0.33227, 0.333144, 0.334016, 0.334888, 0.33576, 0.336631, 0.337502,
		0.338372, 0.339241, 0.34011, 0.340979, 0.341847, 0.342714, 0.343581, 0.344447,
		0.345313, 0.346179, 0.347043, 0.347907, 0.348771, 0.349634, 0.350497, 0.351359,
		0.35222, 0.353081, 0.353941, 0.354801, 0.35566, 0.356519, 0.357377, 0.358235,
		0.359092, 0.359949, 0.360804, 0.36166, 0.362515, 0.363369, 0.364223, 0.365076,
		0.365929, 0.366781, 0.367632, 0.368483, 0.369334, 0.370184, 0.371033, 0.371882,
		0.37273, 0.373577, 0.374424, 0.375271, 0.376117, 0.376962, 0.377807, 0.378651,
		0.379495, 0.380338, 0.38118, 0.382022, 0.382864, 0.383704, 0.384545, 0.385384,
		0.386223, 0.387062, 0.3879, 0.388737, 0.389574, 0.39041, 0.391246, 0.392081,
		0.392916, 0.39375, 0.394583, 0.395416, 0.396248, 0.397079, 0.39791, 0.398741,
		0.399571, 0.4004, 0.401229, 0.402057, 0.402884, 0.403711, 0.404538, 0.405364,
		0.406189, 0.407013, 0.407837, 0.408661, 0.409484, 0.410306, 0.411128, 0.411949,
		0.412769, 0.413589, 0.414409, 0.415227, 0.416045, 0.416863, 0.41768, 0.418496,
		0.419312, 0.420127, 0.420942, 0.421756, 0.422569, 0.423382, 0.424194, 0.425006,
		0.425817, 0.426627, 0.427437, 0.428247, 0.429055, 0.429863, 0.430671, 0.431478,
		0.432284, 0.433089, 0.433894, 0.434699, 0.435503, 0.436306, 0.437109, 0.437911,
		0.438712, 0.439513, 0.440313, 0.441113, 0.441912, 0.44271, 0.443508, 0.444305,
		0.445102, 0.445898, 0.446693, 0.447488, 0.448282, 0.449076, 0.449869, 0.450661,
		0.451453, 0.452244, 0.453035, 0.453825, 0.454614, 0.455403, 0.456191, 0.456978,
		0.457765, 0.458552, 0.459337, 0.460122, 0.460907, 0.461691, 0.462474, 0.463257,
		0.464039, 0.46482, 0.465601, 0.466381, 0.46716, 0.467939, 0.468718, 0.469495,
		0.470273, 0.471049, 0.471825, 0.4726, 0.473375, 0.474149, 0.474922, 0.475695,
		0.476467, 0.477239, 0.47801, 0.47878, 0.47955, 0.480319, 0.481088, 0.481856,
		0.482623, 0.48339, 0.484156, 0.484921, 0.485686, 0.48645, 0.487214, 0.487977,
		0.488739, 0.489501, 0.490262, 0.491022, 0.491782, 0.492541, 0.4933, 0.494058,
		0.494815, 0.495572, 0.496328, 0.497084, 0.497839, 0.498593, 0.499347, 0.5001,
		0.500852, 0.501604, 0.502355, 0.503106, 0.503856, 0.504605, 0.505354, 0.506102,
		0.506849, 0.507596, 0.508343, 0.509088, 0.509833, 0.510578, 0.511321, 0.512065,
		0.512807, 0.513549, 0.51429, 0.515031, 0.515771, 0.51651, 0.517249, 0.517987,
		0.518725, 0.519462, 0.520198, 0.520934, 0.521669, 0.522403, 0.523137, 0.52387,
		0.524603, 0.525335, 0.526066, 0.526797, 0.527527, 0.528257, 0.528986, 0.529714,
		0.530442, 0.531169, 0.531895, 0.532621, 0.533346, 0.53407, 0.534794, 0.535518,
		0.53624, 0.536962, 0.537684, 0.538405, 0.539125, 0.539844, 0.540563, 0.541282,
		0.541999, 0.542716, 0.543433, 0.544149, 0.544864, 0.545579, 0.546293, 0.547006,
		0.547719, 0.548431, 0.549142, 0.549853, 0.550563, 0.551273, 0.551982, 0.552691,
		0.553398, 0.554106, 0.554812, 0.555518, 0.556223, 0.556928, 0.557632, 0.558336,
		0.559039, 0.559741, 0.560442, 0.561143, 0.561844, 0.562544, 0.563243, 0.563941,
		0.564639, 0.565336, 0.566033, 0.566729, 0.567425, 0.56812, 0.568814, 0.569507,
		0.5702, 0.570893, 0.571584, 0.572276, 0.572966, 0.573656, 0.574345, 0.575034,
		0.575722, 0.57641, 0.577096, 0.577783, 0.578468, 0.579153, 0.579838, 0.580521,
		0.581205, 0.581887, 0.582569, 0.58325, 0.583931, 0.584611, 0.585291, 0.58597,
		0.586648, 0.587326, 0.588003, 0.588679, 0.589355, 0.59003, 0.590705, 0.591379,
		0.592052, 0.592725, 0.593397, 0.594069, 0.59474, 0.59541, 0.59608, 0.596749,
		0.597417, 0.598085, 0.598752, 0.599419, 0.600085, 0.600751, 0.601416, 0.60208,
		0.602744, 0.603407, 0.604069, 0.604731, 0.605392, 0.606053, 0.606713, 0.607372,
		0.608031, 0.608689, 0.609347, 0.610004, 0.61066, 0.611316, 0.611971, 0.612626,
		0.61328, 0.613933, 0.614586, 0.615238, 0.61589, 0.616541, 0.617191, 0.617841,
		0.61849, 0.619139, 0.619787, 0.620434, 0.621081, 0.621727, 0.622373, 0.623018,
		0.623662, 0.624306, 0.624949, 0.625592, 0.626234, 0.626876, 0.627516, 0.628157,
		0.628796, 0.629435, 0.630074, 0.630712, 0.631349, 0.631986, 0.632622, 0.633257,
		0.633892, 0.634526, 0.63516, 0.635793, 0.636426, 0.637058, 0.637689, 0.63832,
		0.63895, 0.63958, 0.640209, 0.640837, 0.641465, 0.642092, 0.642719, 0.643345,
		0.64397, 0.644595, 0.645219, 0.645843, 0.646466, 0.647089, 0.647711, 0.648332,
		0.648953, 0.649573, 0.650193, 0.650812, 0.65143, 0.652048, 0.652665, 0.653282,
		0.653898, 0.654514, 0.655128, 0.655743, 0.656357, 0.65697, 0.657583, 0.658195,
		0.658806, 0.659417, 0.660027, 0.660637, 0.661246, 0.661855, 0.662463, 0.66307,
		0.663677, 0.664283, 0.664889, 0.665494, 0.666099, 0.666703, 0.667306, 0.667909,
		0.668511, 0.669113, 0.669714, 0.670315, 0.670915, 0.671514, 0.672113, 0.672711,
		0.673309, 0.673906, 0.674502, 0.675098, 0.675694, 0.676289, 0.676883, 0.677477,
		0.67807, 0.678662, 0.679255, 0.679846, 0.680437, 0.681027, 0.681617, 0.682206,
		0.682795, 0.683383, 0.68397, 0.684557, 0.685144, 0.68573, 0.686315, 0.686899,
		0.687484, 0.688067, 0.68865, 0.689233, 0.689815, 0.690396, 0.690977, 0.691557,
		0.692137, 0.692716, 0.693294, 0.693872, 0.69445, 0.695027, 0.695603, 0.696179,
		0.696754, 0.697329, 0.697903, 0.698476, 0.699049, 0.699622, 0.700194, 0.700765,
		0.701336, 0.701906, 0.702476, 0.703045, 0.703614, 0.704182, 0.704749, 0.705316,
		0.705883, 0.706449, 0.707014, 0.707579, 0.708143, 0.708707, 0.70927, 0.709833,
		0.710395, 0.710956, 0.711517, 0.712078, 0.712637, 0.713197, 0.713756, 0.714314,
		0.714872, 0.715429, 0.715986, 0.716542, 0.717097, 0.717652, 0.718207, 0.718761,
		0.719314, 0.719867, 0.720419, 0.720971, 0.721523, 0.722073, 0.722624, 0.723173,
		0.723722, 0.724271, 0.724819, 0.725367, 0.725914, 0.72646, 0.727006, 0.727552,
		0.728097, 0.728641, 0.729185, 0.729728, 0.730271, 0.730813, 0.731355, 0.731896,
		0.732437, 0.732977, 0.733517, 0.734056, 0.734594, 0.735133, 0.73567, 0.736207,
		0.736744, 0.73728, 0.737815, 0.73835, 0.738884, 0.739418, 0.739952, 0.740485,
		0.741017, 0.741549, 0.74208, 0.742611, 0.743141, 0.743671, 0.7442, 0.744729,
		0.745257, 0.745785, 0.746312, 0.746839, 0.747365, 0.74789, 0.748416, 0.74894,
		0.749464, 0.749988, 0.750511, 0.751034, 0.751556, 0.752077, 0.752598, 0.753119,
		0.753639, 0.754158, 0.754677, 0.755196, 0.755714, 0.756231, 0.756748, 0.757265,
		0.757781, 0.758296, 0.758811, 0.759326, 0.75984, 0.760353, 0.760866, 0.761379,
		0.761891, 0.762402, 0.762913, 0.763424, 0.763934, 0.764443, 0.764952, 0.765461,
		0.765969, 0.766476, 0.766983, 0.76749, 0.767996, 0.768501, 0.769006, 0.769511,
		0.770015, 0.770518, 0.771021, 0.771524, 0.772026, 0.772528, 0.773029, 0.773529,
		0.774029, 0.774529, 0.775028, 0.775527, 0.776025, 0.776523, 0.77702, 0.777517,
		0.778013, 0.778509, 0.779004, 0.779499, 0.779993, 0.780487, 0.78098, 0.781473,
		0.781965, 0.782457, 0.782948, 0.783439, 0.78393, 0.78442, 0.784909, 0.785398
	};
	const int atan_table_num = 1024;
	double atan2(double y, double x){
		const double Pi = PI;
		const double Pi_2 = PI / 2.0;
		const double Pi_3_2 = PI * 3.0 / 2.0;
		const bool IsXMinus = (x < 0) ? true : false; //xは負か？
		const bool IsYMinus = (y < 0) ? true : false; //yは負か？

		if(x == 0 && y == 0){
			return 0;
		}else if(x == 0){
			return ((IsYMinus == true) ? (Pi_3_2) : (Pi_2));
		}else if(y == 0){
			return ((IsXMinus == true) ? (Pi) : (0));
		}
		const double absX = x * ((IsXMinus == true) ? -1: 1);
		const double absY = y * ((IsYMinus == true) ? -1: 1);

		const int flag =
			((IsXMinus == true) ? 4: 0) | ((IsYMinus == true) ? 2: 0) | ((absY >= absX) ? 1: 0);
		//p(flag);
		/*
		flag:
		 \5 y 1/
		4 \ | / 0
		----+----x
		6 / | \ 2
		 /7 | 3\
		*/
		const double hvRatio =
			((flag & 1 )?(((double)absX) / ((double)absY)):(((double)absY) / ((double)absX)));
		double TableIdxDbl = hvRatio * (double)(atan_table_num - 1);
		int table_idx = (int)(TableIdxDbl);

		if(TableIdxDbl - table_idx>=0.5){ //四捨五入
			table_idx++;
		}
		const double th = atan_table[table_idx];

		switch(flag){
			case 0: return th;
			case 1: return (Pi_2 - th);
			case 2: return (Pi * 2.0 - th);
			case 3: return (Pi_3_2 + th);
			case 4: return (Pi - th);
			case 5: return (Pi_2 + th);
			case 6: return (Pi + th);
			case 7: return (Pi_3_2 - th);
		}
		return 0;
	}
	float atan2(float y, float x){
		return((float)(atan2((double)y,(double)x)));
	}
#else

double sin(double rad){return std::sin(rad);}
float sin(float rad){return std::sin(rad);}

	double cos(double rad){return std::cos(rad);}
	float cos(float rad){return std::cos(rad);}

	const double atan_table[] ={0};
	const int atan_table_num = 0;
	double atan2(double y, double x){return std::atan2(y,x);}
	float atan2(float y, float x){return std::atan2(y,x);}

#endif
}