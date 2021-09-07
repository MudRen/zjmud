#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�䶷����̨");
	set("channel_id","�䶷��");
	set("long", "���ֺ��ܻ�ս�д�ĵط�������û�й���û�������ͷ�������Ծ��鷢�ӣ�" );
	set("exits", ([
		"south":__DIR__"wudou",
	]));
	set("out_room",__DIR__"wudou");
	set("no_fly",1);
	set("objects", ([
	]));
	setup();
}

void restore_cnd(object me)
{
	mapping cnd;
	string *ks;
	int i;

	me->delete_temp("in_pkd");
	me->remove_all_enemy(1);
	me->remove_all_killer();
	me->clear_condition();
	me->receive_damage("qi", 0);
	me->apply_killer(me->query_temp("backup/killer"));
	me->apply_want(me->query_temp("backup/want"));
	cnd = me->query("backup/condition");
	me->delete("backup/condition");
	if (! mapp(cnd)) return;
	ks = keys(cnd);
	for (i = 0; i < sizeof(ks); i++)
		me->apply_condition(ks[i], cnd[ks[i]]);
}

void no_die(object me)
{
	object ob;

	if(objectp(ob = me->query_last_damage_from()))
	{
		tell_object(me,"�㲻��"+ob->name()+"�˳����䶷����\n");
	}
	restore_cnd(me);
}

int valid_leave(object me, string dir)
{
	tell_object(me,"���������䶷����̨��\n");
	restore_cnd(me);
	return ::valid_leave(me, dir);
}
