// buildroom.c

// ���Ǽ̳����ַ������͵ģ������Խ��췿�ݡ�
// buildroom �ǿ��Ա������ݵĶ��󣬼̳��߱�����/d/...Ŀ¼�������
// ������ʱ���Ĵ����ļ�������Ϊ��/data/room/...��
//
// ��ҽ���ķ��ݱ�����private_room���mapping���档
// mapping�Ľṹ��
// room_id : room_name
//
// ������
// create_room    :�����ݷ��ݵ����ֺ�ID����ڽ�����ҷ��ݡ�
// query_room_name:�����ؾ��и����ֵķ��ݵĴ��š�
// query_room_id  :�����ؾ��иô��ŵķ��ݵ����֡�

#pragma save_binary

#include <ansi.h>

inherit ROOM;
inherit F_OBSAVE;

string query_room_id(string room_id);
string query_room_name(string room_name);
string query_save_file();
int create_room(string room_name, string room_id, string entry);
int destroy_room(string room_id);

int is_build_room() { return 1; }

int restore()
{
	// this object (/inherit/room/buildroom) doesn't need to save
	if (base_name(this_object()) + ".c" == __FILE__)
		return 0;

	return ::restore();
}

int save()
{
	int res;

	// this object (/inherit/room/buildroom) doesn't need to save
	if (base_name(this_object()) + ".c" == __FILE__)
		return 0;

	return ::save();
}

void setup()
{
	::setup();
	restore();

	return 0;
}

void remove()
{
	save();
}

mixed save_dbase_data()
{
	mapping data;

	data = ([ "exits" : query("exits") ]);
	if (mapp(query("private_room")))
		data += ([ "private_room" : query("private_room") ]);

	return data;
}

int receive_dbase_data(mixed data)
{
	int i;

	if (! mapp(data))
		return 0;

	if (mapp(data["private_room"]))
		set("private_room", data["private_room"]);

	if (mapp(data["exits"]))
	{
		string *ks;

		ks = keys(data["exits"]);
		for (i = 0; i < sizeof(ks); i++)
			// �������ӳ��ڣ����ܼ����ԭ���ĳ��ڣ�����
			// ���ļ��ĳ����޸Ľ����ϡ�
			if (! stringp(query("exits/" + ks[i])))
				set("exits/" + ks[i], data["exits"][ks[i]]);
	}

	return 1;
}

string long()
{
	mapping proom;
	string *idk;
	string desc;
	string line;
	int i, k;

	desc = query("long");
	proom = query("private_room");
	if (! proom || ! sizeof(proom))
		return desc;

	line = "    ����������";
	idk = sort_array(keys(proom), 1);
	k = sizeof(idk) - 1;
	for (i = 0; i <= k; i++)
	{
		if (strlen(line) > 70)
		{
			desc += line + "\n";
			line = "";
		}
		line += proom[idk[i]] + "(" HIC + idk[i] + NOR ")";
		line += i < k ? "��" : "��";
	}
	if (line != "")
		desc += line + "\n";

	return desc;
}

int create_room(string room_name, string room_id, string entry)
{
	if (previous_object() && getuid(previous_object()) != ROOT_UID)
	{
		write(sprintf(HIY "Failed to create room:%s(%s) "
			      "becuase of not root executing it."NOR"\n",
			      room_id, room_name));
		return 0;
	}

	if (query_room_id(room_id) ||
	    query_room_id(room_name))
	{
		write(sprintf(HIY "Failed to create room:%s(%s) "
			      "becuase the same room existed already."NOR"\n",
			      room_name, room_id));
		return 0;
	}

	set("private_room/" + room_id, room_name);
	set("exits/" + room_id, entry);
	return save();
}

int destroy_room(string room_id)
{
	object ob;

	ob = previous_object();
	if (ob && getuid(ob) != ROOT_UID)
		return 0;

	delete("private_room/" + room_id);
	delete("exits/" + room_id);
	return save();
}

string query_room_id(string room_id)
{
	string room_name;

	room_name = query("private_room/" + room_id);
	if (room_name) return room_name;

	room_name = query("exits/" + room_id);
	return room_name;
}

string query_room_name(string room_name)
{
	mapping proom;
	string *idk;
	int i, k;

	proom = query("private_room");
	if (! proom || ! sizeof(proom))
		return 0;

	idk = keys(proom);
	for (i = 0; i < sizeof(idk); i++)
	{
		if (proom[idk[i]] == room_name)
			return idk[i];
	}

	return 0;
}

int query_room_count(string room_name)
{
	if (mapp(query("private_room")))
		return sizeof(query("private_room"));

	return 0;
}

string query_save_file()
{
	string file;
	string arg;

	file = base_name(this_object());

	if (! file || ! sscanf(file, "/d/%s", arg)) return 0;
	return DATA_DIR + file;
}

