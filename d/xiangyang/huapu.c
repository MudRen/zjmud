// Room: /d/xiangyang/huapu.c  ����
// Date: Jan. 28 2002 by Pound

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "����");
	set("long", @LONG
���Ǵ�·����ʮ�ɴ��Ĵ��ԣ�����֮���м���é�ᣬ����Զ������
�±������̡�һ�����಼���ӵĴ�Ů�������������ݣ����е�������
�������ÿ��Ϧ���䵽ɽ�꣬��ⷴ�գ� ����һ��Ƭ������lan hua��֮
�ϣ��ԻͲ��ã����ǻ�����
LONG );
	set("outdoors", "xiangyang");

	set("exits", ([
	    "west"  : __DIR__"caodi4",
	    "east"  : __DIR__"maoshe",
	    "north" : __DIR__"xibian",
	    "south" : __DIR__"huapu2",
	]));
	set("item_desc", ([
	    "lan hua" : "�˻����㵭��������ɫ����������״���أ�ÿ�仨������һֻЬ�ӡ�\n",   
	]));
	set("objects", ([
	    CLASS_D("hu") + "/cheng" : 1,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	object *inv;
	int i;
	inv = all_inventory(me);

	if (dir == "east") 
	{
	    for (i = 0; i < sizeof(inv); i++)
	    {
		if (inv[i]->is_character())
		    return notify_fail("�����Ȱѿ��ŵĶ��������ٽ�ȥ��\n");
	    }
	}

	if (! wizardp(me) && me->query("family/family_name") != "�������" &&
	    objectp(present("cheng lingsu", environment(me))) && dir == "east")
	    return notify_fail("��Ů������üͷ��ס�����ȥ·��\n");

	return ::valid_leave(me, dir);
}