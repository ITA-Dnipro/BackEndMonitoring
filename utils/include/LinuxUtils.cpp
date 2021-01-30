#include "stdafx.h"
#include "PlatformUtils.h"

#ifdef _linux_

CBaseSocket::CBaseSocket()
{
	m_socket = InitSocket();
}

CBaseSocket::~CBaseSocket()
{ 
	PlatformUtils::CloseSocket(m_socket);
}

int CBaseSocket::InitSocket()
{
	return ::socket(AF_INET, SOCK_STREAM, 0);
}


namespace PlatformUtils
{
	bool InitializeWinLibrary()
	{ 
		return true;
	}

	bool FinalizeWinLibrary()
	{ 
		return true;
	}

	bool BindSocket(int socket, sockaddress& current_address)
	{
		if (::bind(socket, (struct SOCKADDR*)&current_address,
			sizeof(current_address)) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool Listen(int socket)
	{
		if (listen(socket, SOMAXCONN) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	int Accept(int socket)
	{
		return static_cast<int>(accept(socket, 0, 0));
	}

	bool Connect(int socket, sockaddress& current_address)
	{
		return connect(socket, (struct sockaddr*)&current_address,
	}

	bool SetUnblockingSocket(int socket)
	{
		int dontblock = 1;
		if (ioctl(socket, FIONBIO, (char*)&dontblock) == SUCCESS)
		{
			return true;
		}
		return false;
	}

	bool CloseSocket(int socket)
	{
		if (socket != SOCKET_INVALID)
		{
			if (close(socket) != ERROR_SOCKET)
			{
				return true;
			}
		}
		return false;
	}

	bool TryGetLogicalDisksNames(std::vector<std::string>& all_disks_names)
	{
		constexpr char path_dev[] = { "/dev" };
		constexpr char loop_ignore[] = { "loop" };
		std::vector<std::string> all_received_names;
		//get all names of disks disks to mount
		for (const auto& file : std::filesystem::directory_iterator(path_dev))
		{
			if (file.is_block_file() &&
				(std::string::npos ==
					file.path().filename().string().find(loop_ignore)))
			{
				all_received_names.emplace_back(
					file.path().filename().string());
			}
		}
		//mount all disks;
		const std::string mount_dir = "/media/disks";
		if (!std::filesystem::exists(mount_dir))
		{
			//make permision only /root 
			if (!std::filesystem::create_directory(mount_dir))
			{
				return false;
			}
			std::filesystem::permissions(
				mount_dir, std::filesystem::perms::group_all |
				std::filesystem::perms::owner_all);
		}
		for (unsigned short i = 0; i < all_received_names.size(); ++i)
		{
			std::string path_to_mount_dir = mount_dir + "/" +
				all_received_names[i];

			if (!std::filesystem::exists(path_to_mount_dir))
			{
				if (!std::filesystem::create_directory(path_to_mount_dir))
				{
					return false;
				}
			}
			//todo: try again make as API
			//mount((path + "/" + all_mounted_disks_path[i]).c_str(), 
			//(mount_dir + "/" + all_mounted_disks_path[i]).c_str(), 
			//NULL, 0, NULL);

			const std::string system_utils_mount_disk =
				(static_cast<std::string>("mount ") + path_dev + "/" +
					all_received_names[i] + " " + path_to_mount_dir);
			system(system_utils_mount_disk.c_str());
			system("clear");
			//if mount to path_to_mount_dir FAIL, then delete name of 
			//dir and delete created dir 
			if (std::filesystem::is_empty(path_to_mount_dir))
			{
				//write to log
				all_received_names.erase(all_received_names.begin() + i);
				std::filesystem::remove(path_to_mount_dir);
				continue;
			}

			all_disks_names.emplace_back(path_to_mount_dir);
		}

		return !all_disks_names.empty();
	}

}

#endif