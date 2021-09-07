#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "ǧ����");
	set("long","ǧ�������̺�����֮����ʹ�������ٶȼӿ죬ÿ����һ�������ٶȱ��һ�֣�ֻ��Խ�������Ѷ�Խ��");

	set("objects",([
	]));
	set("npcs",([
	]));
	set("exits", ([
		"south" : "/d/huashan/qianchi",
		"north" : "/d/lunjian/enter",
	]));
	set("action_list", ([
		"��������" : "niliu",
	]));
	set("no_fight", 1);
    setup();
}
void init()
{
	add_action("niliu", "niliu");
}

int niliu()
{
	object me,slnpc,slroom,*slrooms;
	mixed last,now;
	mapping fam;
	int lvl,i;
	string *slnpcs;
	now = localtime(time());
	me = this_player();

	if(me->query("combat_exp")<800000){
		tell_object(me,"���ʵս����̫�ͣ�����������������\n");
		return 1;
	}
	if(me->query_condition("killer")){
		tell_object(me,"�����ڱ�ͨ��������������������\n");
		return 1;
	}

	if(me->query("last_qianchi")) last = localtime(me->query("last_qianchi"));
	else last = localtime(0);
	if(now[7]==last[7]&&!this_player()->query("qianchi")){
		tell_object(me,ZJOBLONG"�㱾�γ���ѽ�����������������\n");
		return 1;
	}
	slrooms = children("/d/fuben/qianchipu/qianchipu2");
	for (i = 0; i < sizeof(slrooms); i++) {
		if(slrooms[i]->query("owner")==me->query("id"))
			slroom = slrooms[i];
	}
	if(!slroom)
	{
		slroom = new("/d/fuben/qianchipu/qianchipu2");
		slroom->set("owner",me->query("id"));
		if(!me->query("qianchi")){
			lvl = to_int(pow(to_float(me->query("combat_exp")*10),0.333333333))/10;
			if(lvl<1) lvl = 1;
			me->set("qianchi",lvl);
			me->set("last_qianchi",time());
		}
		slroom->set("sllv",me->query("qianchi"));
		slnpcs = ({
			__DIR__"npc/sldz",
		});
		slnpc = new(slnpcs[random(sizeof(slnpcs))]);
		slnpc->set("name",me->query("qianchi")+"������");
	}
	this_player()->move(slroom);
	if(objectp(slnpc))
		slnpc->move(slroom);
	return 1;
}
