//      bieyuan.c ѩɽ��Ժ
inherit ROOM;

void create()
{
	set("short", "ѩɽ��Ժ");
	set("long", @LONG
������ѩɽ�µķֲ������깱�Ʋִ����ﲻԶ�����
����ʥ������Ϊ��ʦ�����ڴ˴�����𷨡�
LONG );
	set("exits", ([
		"east" : "/d/beijing/road5",
	]));
	set("objects" , ([
		__DIR__"npc/seng-bing1"  : 2 ,
		CLASS_D("xueshan") + "/guoshi" : 1 ,
	]));

	set("item_desc", ([
		"�����ӡ�" : "���������ͨ���ܵ�ǰ��ѩɽ�¡�\n"
		ZJOBACTS2"���ֳ�ת:say ���ֳ�ת\n",
	]));
	set("no_fight", 1);

	setup();
}

int valid_leave(object me, string dir)
{
	if (me->query("id") == "seng bing" && dir == "east") return 0;

	return ::valid_leave(me, dir);
}

