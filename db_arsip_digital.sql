-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Waktu pembuatan: 27 Jun 2026 pada 00.30
-- Versi server: 10.4.32-MariaDB
-- Versi PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_arsip_digital`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `aktivitas`
--

CREATE TABLE `aktivitas` (
  `id_log` int(11) NOT NULL,
  `id_user` int(11) DEFAULT NULL,
  `aktivitas` varchar(100) DEFAULT NULL,
  `waktu` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data untuk tabel `aktivitas`
--

INSERT INTO `aktivitas` (`id_log`, `id_user`, `aktivitas`, `waktu`) VALUES
(1, 1, 'Login', '2026-06-26 02:43:59'),
(2, 1, 'Tambah Dokumen', '2026-06-26 02:43:59'),
(3, 2, 'Upload Dokumen', '2026-06-26 02:43:59'),
(4, 3, 'Melihat Laporan', '2026-06-26 02:43:59'),
(5, 4, 'Mencari Dokumen', '2026-06-26 02:43:59'),
(6, 1, 'Login Sistem', '2026-06-26 22:32:14'),
(7, 1, 'Login Sistem', '2026-06-26 22:36:27'),
(8, 1, 'Login Sistem', '2026-06-26 22:41:03'),
(9, 1, 'Login Sistem', '2026-06-26 22:50:02'),
(10, 1, 'Login Sistem', '2026-06-26 23:04:32'),
(11, 1, 'Logout Sistem', '2026-06-26 23:05:01'),
(12, 3, 'Login Sistem', '2026-06-26 23:05:14'),
(13, 5, 'Login Sistem', '2026-06-26 23:13:52'),
(14, 1, 'Login Sistem', '2026-06-26 23:27:04'),
(15, 1, 'Login Sistem', '2026-06-27 00:53:56'),
(16, 1, 'Menambahkan User', '2026-06-27 00:56:57'),
(17, 1, 'Login Sistem', '2026-06-27 01:36:28'),
(18, 1, 'Menambahkan Dokumen', '2026-06-27 01:38:53'),
(19, 1, 'Login Sistem', '2026-06-27 01:44:26'),
(20, 1, 'Login Sistem', '2026-06-27 03:07:59'),
(21, 1, 'Login Sistem', '2026-06-27 04:58:33'),
(22, 1, 'Login Sistem', '2026-06-27 05:03:05'),
(23, 1, 'Login Sistem', '2026-06-27 05:07:27'),
(24, 1, 'Login Sistem', '2026-06-27 05:08:33'),
(25, 1, 'Login Sistem', '2026-06-27 05:09:22'),
(26, 1, 'Login Sistem', '2026-06-27 05:11:09');

-- --------------------------------------------------------

--
-- Struktur dari tabel `dokumen`
--

CREATE TABLE `dokumen` (
  `id_dokumen` int(11) NOT NULL,
  `nomor_dokumen` varchar(50) DEFAULT NULL,
  `judul_dokumen` varchar(100) DEFAULT NULL,
  `tanggal_upload` date DEFAULT NULL,
  `file_dokumen` varchar(255) DEFAULT NULL,
  `deskripsi` text DEFAULT NULL,
  `id_user` int(11) DEFAULT NULL,
  `id_kategori` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data untuk tabel `dokumen`
--

INSERT INTO `dokumen` (`id_dokumen`, `nomor_dokumen`, `judul_dokumen`, `tanggal_upload`, `file_dokumen`, `deskripsi`, `id_user`, `id_kategori`) VALUES
(1, '001/SP/2026', 'Surat Undangan Rapat', '2026-06-26', 'rapat.pdf', 'Undangan rapat tahunan', 1, 1),
(2, '002/SP/2026', 'Surat Edaran Akademik', '2026-06-26', 'edaran.pdf', 'Informasi akademik semester baru', 2, 3),
(3, '003/SP/2026', 'Surat Tugas Dosen', '2026-06-26', 'tugas.pdf', 'Surat tugas kegiatan seminar', 2, 3),
(4, '004/SP/2026', 'Laporan Keuangan Bulanan', '2026-06-26', 'keuangan.pdf', 'Laporan keuangan bulan Juni', 1, 4),
(5, '1', 'Surat Undangan Rapat Mahasiswa', '2026-06-26', 'Rapat Mahasiswa', 'Undangan Rapat Membahas Acara Penerimaan Mahasiswa Baru', 1, 1);

-- --------------------------------------------------------

--
-- Struktur dari tabel `kategori`
--

CREATE TABLE `kategori` (
  `id_kategori` int(11) NOT NULL,
  `nama_kategori` varchar(100) DEFAULT NULL,
  `keterangan` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data untuk tabel `kategori`
--

INSERT INTO `kategori` (`id_kategori`, `nama_kategori`, `keterangan`) VALUES
(1, 'Surat Masuk', 'Arsip surat masuk'),
(2, 'Surat Keluar', 'Arsip surat keluar'),
(3, 'Dokumen Akademik', 'Dokumen akademik'),
(4, 'Dokumen Keuangan', 'Dokumen keuangan');

-- --------------------------------------------------------

--
-- Struktur dari tabel `user`
--

CREATE TABLE `user` (
  `id_user` int(11) NOT NULL,
  `nama` varchar(100) DEFAULT NULL,
  `username` varchar(50) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  `role` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data untuk tabel `user`
--

INSERT INTO `user` (`id_user`, `nama`, `username`, `password`, `email`, `role`) VALUES
(1, 'Doni Susanto', 'Doni', '139', 'doni@gmail.com', 'Admin'),
(2, 'Mohammad Imam Merintria', 'Imam', '137', 'imam@gmail.com', 'Petugas'),
(3, 'Muhammad Ode Excel N', 'Ode', '147', 'excel@gmail.com', 'Pimpinan'),
(4, 'Muhamad Yusri', 'Yusri', '142', 'yusri@gmail.com', 'User'),
(5, 'Alkausar', 'Kausar', '123', 'kausar@gmail.com', 'User'),
(6, 'Aulia Dewi', 'Aulia', '123', 'aulia@gmail.com', 'User');

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `aktivitas`
--
ALTER TABLE `aktivitas`
  ADD PRIMARY KEY (`id_log`),
  ADD KEY `id_user` (`id_user`);

--
-- Indeks untuk tabel `dokumen`
--
ALTER TABLE `dokumen`
  ADD PRIMARY KEY (`id_dokumen`),
  ADD KEY `id_user` (`id_user`),
  ADD KEY `id_kategori` (`id_kategori`);

--
-- Indeks untuk tabel `kategori`
--
ALTER TABLE `kategori`
  ADD PRIMARY KEY (`id_kategori`);

--
-- Indeks untuk tabel `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id_user`);

--
-- AUTO_INCREMENT untuk tabel yang dibuang
--

--
-- AUTO_INCREMENT untuk tabel `aktivitas`
--
ALTER TABLE `aktivitas`
  MODIFY `id_log` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- AUTO_INCREMENT untuk tabel `dokumen`
--
ALTER TABLE `dokumen`
  MODIFY `id_dokumen` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT untuk tabel `kategori`
--
ALTER TABLE `kategori`
  MODIFY `id_kategori` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT untuk tabel `user`
--
ALTER TABLE `user`
  MODIFY `id_user` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- Ketidakleluasaan untuk tabel pelimpahan (Dumped Tables)
--

--
-- Ketidakleluasaan untuk tabel `aktivitas`
--
ALTER TABLE `aktivitas`
  ADD CONSTRAINT `aktivitas_ibfk_1` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`);

--
-- Ketidakleluasaan untuk tabel `dokumen`
--
ALTER TABLE `dokumen`
  ADD CONSTRAINT `dokumen_ibfk_1` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`),
  ADD CONSTRAINT `dokumen_ibfk_2` FOREIGN KEY (`id_kategori`) REFERENCES `kategori` (`id_kategori`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
