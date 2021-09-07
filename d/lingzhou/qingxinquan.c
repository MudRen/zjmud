// Room: /lingzhou/qingxinquan.c

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����Ȫ");
	set("long", @LONG
����ɽ�е�һ����Ȫ��λ���ֳ������ɽ���ϣ���Χ�Ǵ��̵�������
������ɽȪˮ��Ȫ�ۻ�����ӿ�����۳�һ��С̶��С̶ˮ���������ɽ
�£��Ա�һ��С·ͨ��ɽ�¡�
LONG );
	set("exits", ([
		"south" : __DIR__"kongdi",
		"north" : __DIR__"wangling",
	]));
	set("objects", ([
	]));
	set("action_list", ([
		"��������":"wlzb",
	]));
	set("resource/water", 1);
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	setup();
}

void init()
{
	add_action("zhengba","wlzb");
}

int zhengba()
{
	string banghui;
	object wushi,room,me = this_player();

	if(!mapp(me->query("banghui")))
		return notify_fail("���˵��ƹ£����ȼ���һ����������ɣ�\n");
	if(me->query("last_wlzb")/86400==time()/86400)
		return notify_fail("������Ѿ��μӹ������������ˣ�\n");

	banghui = me->query("banghui/name");

	if(WARS_D->query_data("wangling/"+banghui+"/users/"+me->query("id")))
		return notify_fail("������Ѿ�������μӹ����������ˣ����������ɣ�\n");

	WARS_D->set_data("wangling/"+banghui+"/users/"+me->query("id"),1);
	WARS_D->set_data("wangling/"+banghui+"/pot",WARS_D->query_data("wangling/"+banghui+"/pot")+1);

	room = new(__DIR__"wlroad");
	wushi = new(__DIR__"npc/shiwushi");
	wushi->move(room);
	room->set("start_time",time());
	me->move(room);
	wushi->kill_ob(me);
	me->kill_ob(wushi);
	me->set("last_wlzb",time());
	tell_object(me,"����������������ڵ�ͨ������ǰһ��ʯ��������ס�����ȥ·��Ϊ�˰�����������ȫ���������ɣ�Ϊ���������ս�����������ܵ��ͷ���\n");
	room->set_heart_beat(1);

	return 1;
}

int valid_leave(object me, string dir)
{
	if(dir=="north")
	{
		tell_object(me,"������������ս��δ���ţ�");
		return 0;
	}
	return ::valid_leave(me, dir);
}
