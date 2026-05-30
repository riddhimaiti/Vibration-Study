\documentclass[12pt, a4paper]{article}
\usepackage[utf8]{inputenc}
\usepackage{geometry}
\geometry{a4paper, margin=1in}
\usepackage{graphicx}
\usepackage{hyperref}
\usepackage{titlesec}
\usepackage{caption}
\usepackage{float}
\usepackage{listings}
\usepackage{xcolor}

% Setup for code listings
\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{backcolour}{rgb}{0.95,0.95,0.92}
\lstdefinestyle{mystyle}{
    backgroundcolor=\color{backcolour},
    commentstyle=\color{codegreen},
    keywordstyle=\color{magenta},
    numberstyle=\tiny\color{codegray},
    stringstyle=\color{codepurple},
    basicstyle=\ttfamily\footnotesize,
    breakatwhitespace=false,
    breaklines=true,
    captionpos=b,
    keepspaces=true,
    numbers=left,
    numbersep=5pt,
    showspaces=false,
    showstringspaces=false,
    showtabs=false,
    tabsize=2
}
\lstset{style=mystyle}

\title{\textbf{Vibration Study of 2.2 Road (Gymkhana to Nehru Museum), IIT Kharagpur}}
\author{
    \textbf{Prepared by: C2G15 Group} \\
    P Prajit – 24MF10047 \\
    Riddhi Maiti – 24MF10051 \\
    Nare Mahith Sai – 24MF10043
}
\date{November 12, 2025}

\begin{document}

\maketitle

\begin{abstract}
This report documents a vibration measurement study carried out along the 2.2 Road route from Gymkhana to Nehru Museum at IIT Kharagpur. Measurements were taken by riding a campus toto equipped with two inertial sensors (MPU6050 and ADXL345) and a GPS receiver to provide geographic tagging. The objective of this study was to characterize road roughness and the in-vehicle vibrational environment, ultimately providing actionable recommendations for road maintenance and vehicle comfort. \newline\newline
\textbf{Note:} This project was partially inspired by Professor Vikranth Racherla’s case study on the dynamics of bogeys.
\end{abstract}

\newpage
\tableofcontents
\newpage

\section{Problem Statement}
Road roughness and localized defects cause vehicle vibrations that negatively affect passenger comfort and vehicle fatigue life, while also serving as indicators of pavement deterioration. The 2.2 Road between Gymkhana and Nehru Museum at IIT Kharagpur is used frequently by campus vehicles, including totos. The goal of this study is to quantify the vibration levels experienced during a typical toto ride along this route, identify hotspots with elevated vibrations, and provide engineering metrics along with actionable recommendations for maintenance.

\paragraph{Key Questions:}
\begin{itemize}
    \item Where along the route are the vibration levels unusually high (hotspots)?
    \item How do the two accelerometers (MPU6050 and ADXL345) compare in their measured responses?
    \item What do the extracted vibration metrics imply about passenger comfort and current pavement conditions?
\end{itemize}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure1.png}
\caption{Route Map (Gymkhana to Nehru Museum)}
\end{figure}

\section{State of the Art}
\begin{itemize}
    \item Road roughness is commonly quantified using profile-derived indices, such as the International Roughness Index (IRI), or accelerometer-derived metrics including RMS acceleration, power spectral density, and Vibration Dose Value (VDV).
    \item Accelerometers mounted in vehicles are widely used for rapid road condition surveys when dedicated profilometers are unavailable.
    \item Low-cost MEMS accelerometers, such as the MPU6050 and ADXL345, have been shown in numerous studies to be adequate for relative road condition mapping when appropriately calibrated and filtered.
    \item Typical limitations of these sensors include bias instability, temperature sensitivity, and reduced accuracy at very low frequencies.
    \item GPS (NMEA) data are crucial for geolocating measurement windows and computing vehicle speed.
    \item Careful timestamp synchronization between GPS and IMU data is necessary to ensure reliable hotspot mapping.
    \item Standard guidance on human exposure to whole-body vibration is outlined in the ISO 2631 series (e.g., ISO 2631-1), which describes metrics such as VDV for comfort evaluation.
\end{itemize}

\section{Objectives}
\begin{itemize}
    \item Acquire synchronized 3-axis accelerometer data and GPS position/time data along the entire 2.2 Road route using a toto as the measurement platform.
    \item Process raw sensor data to remove noise and bias, align timebases, and transform sensor axes to vehicle axes as required.
    \item Compute vibration metrics per road segment, including RMS acceleration, peak values, and VDV where applicable.
    \item Produce a geolocated vibration heatmap illustrating hotspots along the route and provide a ranked list of problematic locations.
    \item Compare the MPU6050 and ADXL345 accelerometers for consistency to recommend best practices for future surveys.
    \item Provide recommendations for road maintenance, ride comfort improvement, and future measurement enhancements.
\end{itemize}

\section{Work Plan and Schedule}
\paragraph{Phase 1 — Preparation (1 week)}
\begin{itemize}
    \item Finalize the sensor mounting and logging system.
    \item Write and verify the data-logging firmware.
    \item Conduct pre-test bench calibration.
\end{itemize}
\paragraph{Phase 2 — Field Data Collection (1–3 days)}
\begin{itemize}
    \item Perform multiple runs (a minimum of 2 runs during similar daytime conditions and passenger loads) along the route at typical toto speeds.
    \item Record environmental notes such as weather, passenger load, and route deviations.
\end{itemize}
\paragraph{Phase 3 — Data Processing \& Analysis (1–2 weeks)}
\begin{itemize}
    \item Preprocess the data by resampling, time-syncing, filtering, and removing offsets.
    \item Compute metrics per fixed-length segments (e.g., 10 m or 50 m windows) to identify hotspots.
\end{itemize}
\paragraph{Phase 4 — Reporting \& Recommendations (1 week)}
\begin{itemize}
    \item Create visualizations, map overlays, and finalize the report.
\end{itemize}

\section{Equipment \& Specifications}
\begin{itemize}
    \item \textbf{MPU6050:} A 3-axis accelerometer and 3-axis gyroscope featuring a configurable accelerometer range of $\pm$2/$\pm$4/$\pm$8/$\pm$16 g and internal sampling via I2C.
    \item \textbf{ADXL345:} A 3-axis accelerometer with selectable ranges of $\pm$2/$\pm$4/$\pm$8/$\pm$16 g and a digital I2C interface.
    \item \textbf{GPS module (Neo-6M):} Provides UTC position and time via NMEA sentences, capable of logging at 1--10 Hz.
    \item \textbf{Arduino Uno:} Serves as the microcontroller for data acquisition and timestamps.
    \item \textbf{Laptop / Software:} Utilizes Python (pandas, numpy, scipy, matplotlib) for data handling, folium for mapping, and Jupyter for processing.
\end{itemize}

\section{Connection Diagram}
The project utilizes a circuit connected via a breadboard integrating the Arduino Uno, GPS NEO-6M, MPU6050, and ADXL345.

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure2.png}
\caption{Fritzing Connection Diagram}
\end{figure}

\section{Results}
The data collection yielded several major graphical interpretations outlining the vibrational impacts along the route:
\begin{itemize}
    \item \textbf{Raw and Filtered Accelerations:} Visualized across the X, Y, and Z axes for both the MPU6050 and ADXL345 sensors.
    \item \textbf{Ride Comfort Trend:} A graph displaying RMS Dynamic Acceleration computed over 1-second windows, where lower values correlate to a smoother ride and higher values indicate roughness.
    \item \textbf{Detected Road Disturbances:} A resultant acceleration plot highlighting localized bumps and potholes marked by defined peaks.
    \item \textbf{VDV Ride Harshness Index:} Displayed alongside detected bump/pothole events for objective comfort assessment.
    \item \textbf{Geolocation Heatmap:} A visual map noting severity hotspots, speed, and specific acceleration metrics for notable bump locations.
    \item \textbf{Hardware Setup:} The functional circuit was assembled on cardboard plating, double-taped to the floor of the toto, and connected to a laptop running Coolterm for data collection.
\end{itemize}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure3.png}
\caption{Raw and Filtered Acceleration Data}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure4.png}
\caption{Ride Comfort Trend}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure5.png}
\caption{Detected Road Disturbances}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure6.png}
\caption{VDV Ride Harshness Index}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure7.png}
\caption{Geolocation Heatmap}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure8.png}
\caption{Hardware Setup (Arduino Circuit)}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure9.png}
\caption{Circuit in Toto}
\end{figure}

\begin{figure}[H]
\centering
\includegraphics[width=0.9\textwidth]{figure10.png}
\caption{Data Collection with Laptop}
\end{figure}

\section{Discussion}
\begin{itemize}
    \item \textbf{Vehicle Influence:} The soft suspension of the toto inherently increases sensitivity to small bumps. While this is useful for assessing passenger comfort, it implies that measured magnitudes are vehicle-dependent. For structural pavement assessment, vehicle-type correction or reference vehicle data may be required.
    \item \textbf{Sensor Redundancy:} The simultaneous use of both the MPU6050 and ADXL345 improved overall confidence in detected events. Slight amplitude differences are expected due to variations in sensor range, filters, and axis alignment.
    \item \textbf{GPS Limitations:} The standard NEO-6M GPS operating at 1 Hz provides a spatial resolution of roughly 3--5 m at walking speeds. For higher-precision localization, higher-rate GNSS or differential methods are suggested.
    \item \textbf{Repeatability:} Comparing two passes on the identical segment is highly recommended; high repeatability increases confidence in the localized road defects.
\end{itemize}

\section{Conclusions}
\begin{itemize}
    \item Low-cost MEMS accelerometers (MPU6050 and ADXL345) mounted on a toto effectively detected and localized road irregularities along the 2.2 Road at IIT Kharagpur.
    \item The combined IMU and GPS approach produced a detailed spatial map of road roughness that is highly useful for maintenance prioritization.
    \item Sensor fusion alongside proper gravity compensation successfully improved the quality of the derived vibration metrics.
    \item Future improvements could include implementing higher GPS sampling rates, conducting additional passes for statistical validation, and potentially utilizing fleet-based collection to average out vehicle-specific biases.
\end{itemize}

\section{Recommendations}
\begin{itemize}
    \item Prioritize immediate repairs at high-severity hotspots based on collected coordinate data.
    \item Establish a standard mounting plate location and baseline sampling frequency for routine monitoring purposes.
    \item Improve spatial data quality by utilizing a GPS unit with a higher update rate or by attaching an external antenna for a stronger connection.
    \item Consult ISO 2631-1 thresholds during human comfort assessments prior to declaring definitive health risks.
    \item Conduct similar experiments iteratively at varying vehicle speeds while performing a parametric sweep of hyperparameters (e.g., bump peak prominence) to accurately pinpoint major defects and focus maintenance attention effectively.
\end{itemize}

\section{References}
\begin{itemize}
    \item Behaviour of Metro Coach on Newly Built Track in Kolkata – Prof. V. Racherla, Dr. S.K. Singh, Dr. H. Danawe.
    \item MPU-6050 Product Specification (InvenSense) datasheet.
    \item ADXL345 Datasheet (Analog Devices).
\end{itemize}

\newpage
\appendix
\section{Arduino Code}
\begin{lstlisting}[language=C++]
#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

MPU6050 mpu;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(3,4);
Adafruit_ADXL345_Unified adxl = Adafruit_ADXL345_Unified();

unsigned long prevTime;
float prevGx = 0, prevGy = 0, prevGz = 0;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while(1);
  }

  if(!adxl.begin()) {
    Serial.println("ADXL345 not detected. Check wiring!");
    while(1);
  }

  Serial.println("Time(ms),Lat,Lon,Speed(kmph),Ax,Ay,Az,Gx,Gy,Gz,AlphaX,AlphaY,AlphaZ");
  prevTime = millis();
  adxl.setRange(ADXL345_RANGE_2_G);
}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  float Ax = (mpu.getAccelerationX() / 16384.0) * 9.81;
  float Ay = (mpu.getAccelerationY() / 16384.0) * 9.81;
  float Az = (mpu.getAccelerationZ() / 16384.0) * 9.81;

  float Gx = mpu.getRotationX() / 131.0;
  float Gy = mpu.getRotationY() / 131.0;
  float Gz = mpu.getRotationZ() / 131.0;

  unsigned long currTime = millis();
  float dt = (currTime - prevTime) / 1000.0;

  float AlphaX = (Gx - prevGx) / dt;
  float AlphaY = (Gy - prevGy) / dt;
  float AlphaZ = (Gz - prevGz) / dt;

  Serial.print(currTime); Serial.print(",");

  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6); Serial.print(",");
    Serial.print(gps.location.lng(), 6); Serial.print(",");
  } else {
    Serial.print("0,0,");
  }

  if (gps.speed.isValid()) {
    Serial.print(gps.speed.kmph(), 2); Serial.print(",");
  } else {
    Serial.print("0,");
  }

  Serial.print(Ax); Serial.print(",");
  Serial.print(Ay); Serial.print(",");
  Serial.print(Az); Serial.print(",");
  Serial.print(Gx); Serial.print(",");
  Serial.print(Gy); Serial.print(",");
  Serial.print(Gz); Serial.print(",");
  Serial.print(AlphaX); Serial.print(",");
  Serial.print(AlphaY); Serial.print(",");
  Serial.print(AlphaZ);Serial.print(",");

  prevGx = Gx;
  prevGy = Gy;
  prevGz = Gz;
  prevTime = currTime;

  sensors_event_t event;
  adxl.getEvent(&event);
  float Ax_ADXL = event.acceleration.x;
  float Ay_ADXL = event.acceleration.y;
  float Az_ADXL = event.acceleration.z;

  Serial.print("Ax from ADXL: "); Serial.print(Ax_ADXL, 3);
  Serial.print("Ay from ADXL: "); Serial.print(Ay_ADXL, 3);
  Serial.print("Az from ADXL: "); Serial.print(Az_ADXL, 3); Serial.println("");

  delay(10); // 100 Hz IMU logging
}
\end{lstlisting}

\section{Python Code for Data Analysis}
\texttt{Ride Analysis 2.2 Toto.ipynb}

\end{document}
