#include <ansi.h>
#define OUT_ROOM "/d/city/guangchang"
inherit ROOM;

int do_leave(string arg);
void create()
{
	set("short", "����һ��");
	set("long","�����������ڱ����ĵ�һ�㣬�䱸ɭ�ϣ�һ����֪����Ѻ����Ҫ���\n");
	set("out_room", OUT_ROOM);
	set("exits", ([
		"south" : OUT_ROOM,
	]));
	setup();
}

void nextlv(int delay)
{
	add("sllv",1);
	set("short", "����"+CHINESE_D->chinese_number(query("sllv"))+"��");
	set("long","�����������ڱ����ĵ�"+CHINESE_D->chinese_number(query("sllv"))+"�㣬�䱸ɭ�ϣ�һ����֪����Ѻ����Ҫ���\n");
	tell_room(this_object(),ZJFORCECMD("look"));
	call_out("nextlv2",delay);
}

int nextlv2()
{
	object slnpc;
	slnpc = new("/clone/fuben/wanansi/npc/hero");
	slnpc->move(this_object());
	slnpc = new("/clone/fuben/wanansi/npc/sldizi");
	slnpc->move(this_object());
	tell_room(this_object(),"��������"+query("short")+"��\n");
	return 1;
}

void no_die(object ob)
{
	object *inv,env;
	int i;
	int k = 0;

	env = environment(ob);
	inv = all_inventory(env);
	for(i=0;i<sizeof(inv);i++)
	{
		if(inv[i]!=ob&&playerp(inv[i])) k = 1;
	}
	if(!k)
		call_out("des_me",1);
	ob->delete("wanan");
}

int valid_leave(object me, string dir)
{
	no_die(me);
	return ::valid_leave(me, dir);
}

void des_me()
{
	destruct(this_object());
}