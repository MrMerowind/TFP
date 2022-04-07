/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef DATEANDTIME_HPP_INCLUDED
#define DATEANDTIME_HPP_INCLUDED

namespace tfp{
    /// Zwraca ilosc sekund od 1970 roku
    time_t Seconds();
    ////////////////////////////////////////////////////
    /// Zwraca date w wybranym formacie np "Y.M.D h:m:s"
    /// Zwraca date w podanum formacie aktualnego czasu lub podanego
	/// 	jako drugi parametr
	/// 	Format:
	/// 		Y - rok
	/// 		M - miesiac
	/// 		D - dzien
	/// 		h - godzina
	/// 		m - minuta
	/// 		s - sekunda
	/// 		\Y - Y
	/// 		\M - M
	/// 		itd.
	////////////////////////////////////////////////////
    std::string Date(std::string Format, time_t Time = time(nullptr));
};

#endif // DATEANDTIME_HPP_INCLUDED
