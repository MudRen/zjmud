inherit ROOM;

void create()
{
	set("short","˾ͽ��");
	set("long",@LONG
�����Ǵ����˾ͽ�á�������������������������Բ����ԡ�
�����������ֵ��ǵ��Ͻ��仹����Щ������������֮������¡�
LONG);
	set("objects", ([
		CLASS_D("duan") + "/hua" : 1,
	]));
	set("exits",([
		"east"  : __DIR__"zonglichu",
	]));
	setup();
}

