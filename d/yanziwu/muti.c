//ROOM: /d/yanziwu/muti.c

inherit ROOM;

void create()
{
	set("short", "ľ��");
	set("long",@LONG
����һ������֦�ܳɵ�ľ�ݣ�������ͨ��ˮ�档�������Ա���֦��
һֻС�� "ɯɯ��ɯ��ɯɯ��ɯ" �Ľ�����������������һ�����ϱ�ͨ
���롣
LONG );
	set("outdoors", "yanziwu");
	set("exits", ([
	    "eastup" : __DIR__"qinyun",
	    "southup" : __DIR__"bozhou",
	]));
	setup();
}
