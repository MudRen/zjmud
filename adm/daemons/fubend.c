//by ranger.����

#include <ansi.h>

inherit F_DBASE;
varargs int des_fuben(string fuben_sn, int indx);

mapping fuben_list = ([
	"heifeng":	([
				"name":"�ڷ�կ",
				"time":1800,
				"team":5,
			]),
	"wolong":	([
				"name":"������",
				"time":1800,
				"team":1,
			]),
]);

mapping fuben_open;
mapping fuben_where;

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "��������");
	CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������");
	fuben_open = ([]);
	fuben_where = ([]);
	set_heart_beat(30);
}

void heart_beat()
{
	string *fuben, name;
	int i, time, k, j, is_ok;
	string *room_all;
	string *room;
	object *all_inv, ob;
	
	fuben = keys(fuben_open);
	for(i=0;i<sizeof(fuben);i++)
	{
		name = fuben_open[fuben[i]]["name"];
		time = fuben_open[fuben[i]]["time"];
		if((time()-time)>=fuben_list[name]["time"])
			des_fuben(fuben[i]);
	}
}

int create_fuben(object me, string name)
{
	string *files,*dirs,fuben_sn,*list;
	object room;
	mapping fb;
	int i,j,k;

	if(!mapp(fuben_list[name]))
	{
		tell_object(me,"����ʧ�ܣ��޴˸�����\n");
		return 0;
	}
	files = get_dir("/d/fuben/"+name+"/");
	list = ({});
	fb = ([]);
	fuben_sn = sprintf("%s_%d",me->query("id"),time());
	for(i=0;i<sizeof(files);i++)
	{
		if(file_size("/d/fuben/"+name+"/"+files[i])>0)
		{
			room = new("/d/fuben/"+name+"/"+files[i]);

			room->set("fuben_sn",fuben_sn);
			list += ({ file_name(room) });
			if(files[i]=="enter.c")
			{
				room->set("exits/out",base_name(environment(me)));
				fb["enter"] = file_name(room);
			}
		}
	}
	
	for(i=0;i<sizeof(list);i++)
	{
		if(room=find_object(list[i]))
		{
			dirs = keys(room->query("exits"));
			for(j=0;j<sizeof(dirs);j++)
			{
				for(k=0;k<sizeof(list);k++)
				{
					if (strsrch(list[k], room->query("exits/"+dirs[j])+"#")==0) {
						
						room->set("exits/"+dirs[j], list[k]);
						
						if (room->query("anniu_hide"))
						{
							//���ð��ұ��õ�room
							if (dirs[j] == "down") {
								room->set("bei_path", list[k]);
								room->delete("exits/down");
							}
						}
					}
				}
			}
		}
	}

	if(fuben_where[base_name(environment(me))])
		fuben_where[base_name(environment(me))] += ({ fuben_sn });
	else
		fuben_where[base_name(environment(me))] = ({ fuben_sn });

	fb["files"] = list;
	fb["owner"] = me->query("id");
	fb["time"] = time();
	fb["name"] = name;
	fb["where"] = base_name(environment(me));
	fuben_open[fuben_sn] = fb;
	log_file("fuben_d/fuben", sprintf("%s %s %s\n", me->query("name") + "("+me->query("id")+")", 
		"������"+name,
		"λ��"+fb["where"]));
	return 1;
}

string *query_where(string where)
{
	if(fuben_where[where]&&sizeof(fuben_where[where]))
		return fuben_where[where];
	else
		return 0;
}

mapping query_info(string fuben)
{
	mapping info;

	if(!mapp(info=fuben_open[fuben]))
		return 0;

	info["cname"] = fuben_list[info["name"]]["name"];
	info["team"] = fuben_list[info["name"]]["team"];
	return info;
}

varargs int des_fuben(string fuben_sn, int indx)
{
	mapping info;
	string *list;
	object room,*inv;
	int i,j;

	info = fuben_open[fuben_sn];
	list = info["files"];
	for(i=0;i<sizeof(list);i++)
	{
		if(!objectp(room = find_object(list[i]))) continue;
		inv = all_inventory(room);
		for(j=0;j<sizeof(inv);j++)
		{
			if(userp(inv[j]))
			{ 
				if (!indx)
					tell_object(inv[j],HIG"����"+fuben_list[info["name"]]["name"]+"�ڴ���̫���ˣ����ò����˳�����"NOR"\n");
				else
					tell_object(inv[j],HIG"��о�"+fuben_list[info["name"]]["name"]+"��̫�ֲ��ˣ������ȳ���ɡ�"NOR"\n");
				
				inv[j]->move(info["where"]);
			}
		}
		destruct(room);
	}
	fuben_where[info["where"]] -= ({ fuben_sn });
	map_delete(fuben_open, fuben_sn);
	if (sizeof(fuben_where[info["where"]]) < 1)
		map_delete(fuben_where, info["where"]);
	
	return 1;
}

