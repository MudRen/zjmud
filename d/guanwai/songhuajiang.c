// /guanwai/songhuajiang.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�ɻ�����");
	set("long", @LONG
�������ɻ����Ľ��棬�������ѽⶳ���峺�Ľ�ˮ���α�ȥ����������
��������֧���������������е��ڴ�β���Ŷ档
LONG );
	set("no_clean_up", 0);
	set("outdoors", "guanwai");
	setup();
}

void transfer(object *obs, string dest)
{
	obs->move(this_object());
	message("vision", BLU "���ڽ���һ·Ư��......."NOR"\n", obs);
	call_out("arrive", 10, obs, dest);
}

void arrive(object *obs, string dest)
{
	obs = filter_array(obs, (: objectp($1) &&
				   environment($1) == this_object() :));
	if (! sizeof(obs))
		return;
	message("vision", "\n���ܿ�ͣ���˰�����̧�ſ��������\n\n", obs);
	obs->move(dest);
}

