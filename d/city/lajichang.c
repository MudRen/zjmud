// by ranger_����
// heishi.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", "��������������һЩ�������׶����Ķ����������������٣�����֮ǰ�����ؿ��ǣ�������ʧ��");
	set("exits", ([
		"northeast":__DIR__"guangchang",
	]));
	set("objects", ([
	]));
	set("no_fight","1");
	set("no_steal", "1");
	set("no_sleep_room", "1");
	setup();
}

void init()
{
	add_action("do_drop", "drop");
}

int do_drop(string arg)
{
	object ob,me = this_player();
	if(ob=present(arg,me))
	{
		tell_object(me,"�㽫"+ob->short()+"��������������\n");
		log_ufile(me,"laji","��"+ob->short()+"("+file_name(ob)+")������������\n");
		destruct(ob);
	}
	return 1;
}
