// muwu1.c
inherit ROOM;

void create()
{
	set("short", "ľ��");
	set("long", @LONG
������һ�䲻���ľͷ���ӣ�������ȸ��С����ؾ�ȫ��������ֻ����
������ذ��ż����Ҿߣ�����Ҳ���Ե���ôС��
LONG );
	set("exits", ([
		"north" : __DIR__"xiaodao5",
	]));
 	set("objects", ([
		CLASS_D("xiaoyao") + "/kanggl": 1,
	]));
	setup();
}
