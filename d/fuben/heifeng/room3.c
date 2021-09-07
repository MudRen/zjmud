// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǻڷ�կ���ң�����ͷ�����ڴ˴���
LONG
	);
	set("exits", ([
		"south" : __DIR__"room2",
		"down" : __DIR__"room4",
	]));
	set("item_desc", ([
		"�ֻ�" : "����һ���������ղص��ֻ�������񿴵����񱳺���һ����ť��\n"
		ZJOBACTS2"��ť:anniu picture\n",
	]));
	set("objects", ([
		"/d/fuben/npc/tufei": 2,
		"/d/fuben/npc/tufeitou": 1,
		"/d/fuben/obj/baoxiang": 1,
	]));
	set("anniu_hide", 1);
	setup();
}

int do_anniu(string arg)
{
	string room;
	object ob;
	object me = this_player();
	object oba, obb;
	object player;
	int ok = 0;
	object *obs = all_inventory();
	
	oba = present("tu fei", environment(me));
	obb = present("tufei tou", environment(me));
	
	foreach(player in obs) {
		if (userp(player))
		{
			if (oba) {
				oba->kill_ob(player);
				player->kill_ob(oba);
				tell_object(player, oba->name()+"�����������ò��ͷ��ˣ����ڴ�ү��ǰ������\n");
				ok = 1;
			}
			if (obb) {
				obb->kill_ob(player);
				player->kill_ob(obb);
				tell_object(player, obb->name()+"��������������������Ұ����ҿ�����������\n");
				ok = 1;
			}
		}
	}
	if (ok > 0)
		return 1;
	
	if (!arg || arg != "picture") {
		write("�Ұ�ʲô����\n");
		return 1;
	}
	if (me->is_busy())
		return notify_fail("����æ�ţ�\n");
	
	if (query("do_down")) 
		return notify_fail("�Ұ�ʲô����ť�Ѿ����˰����ˣ�\n");
	
	if (!query("do_down") && random(50) > 3) {
		room = this_object()->query("bei_path");
		ob  = find_object(room);
		message_vision("$N�������ֻ�����İ�ť���£�ȴ���õذ�һ��"
							+"������~����~�춯��$N��ͷһ����ǽ��¶��һ�����µ�ͨ��������\n"
										+"$N����֮���������ͣ�ֻ�������ꡱһ������ť��Ȼ��$N�����ˣ���\n", me);
		this_object()->set("exits/down", file_name(ob));
		call_out("do_closed", 600, ob);//10���Ӻ�ر�
	} else {
		message_vision("$N�������ֻ�����İ�ť���£�ȴ���ð�ťһ��"
							+"������~����~�춯����ť��Ȼ��$N�����ˣ���\n", me);
	}
	
	this_object()->set("do_down", 1);
	return 1;
}
void do_closed(object ob)
{	
	if (this_object()) {
		message("vision", "ֻ���ذ�һ���춯�������ͨ����Ȼ�Զ��ر��ˣ�\n", this_object());
		this_object()->delete("exits/down");
	}
	if (ob)
		destruct(ob);
	remove_call_out("do_closed");
}
#include "/d/fuben/room_fb.h"
