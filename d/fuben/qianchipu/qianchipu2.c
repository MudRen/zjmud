#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long","ǧ�������̺�����֮����ʹ�������ٶȼӿ죬ÿ����һ�������ٶȱ��һ�֣�ֻ��Խ�������Ѷ�Խ��");

	set("sllv",1);
	set("objects",([
	]));
	set("exits", ([
		"south" : __DIR__"qianchipu",
	]));
	set("action_list", ([
		"������ս" : "slover",
	]));
	set("cost", 1);
	setup();
}

void init()
{
       add_action("slover", "slover");
       add_action("slover1", "slover1");
}

int slover()
{
	write(ZJOBLONG"��ȷ��Ҫ�������ֳ��ô��\n"ZJOBACTS2"ȷ��:slover1\n");
	return 1;
}
	
int slover1()
{
	object slroom;
	object me = this_player();

	slroom = this_object();

	tell_object(me,sprintf(ZJOBLONG"��������������$br#�����ȼ���%d\n",me->query("qianchi")));
	log_file("qianchi", sprintf("%s��%s���%d��ǧ��������������ֵ=%d��\n",ctime(time()),me->query("id"),me->query("qianchi"),me->query("combat_exp")));
	this_player()->delete("qianchi");
	this_player()->move("/d/fuben/qianchipu/qianchipu");
	this_player()->remove_all_killer();
	destruct(slroom);
	return 1;
}

void nextlv(int delay)
{
	add("sllv",1);
	call_out("nextlv2",delay);
}

int nextlv2()
{
	object slnpc;
	string *slnpcs;

	slnpcs = ({
		__DIR__"npc/sldz",
	});
	slnpc = new(slnpcs[random(sizeof(slnpcs))]);
	slnpc->set("name",query("sllv")+"������");
	slnpc->move(this_object());
	return 1;
}

int valid_leave(object me, string dir)
{
	return ::valid_leave(me, dir);
}
