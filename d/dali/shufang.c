inherit ROOM;

void create()
{
	set("short", "�鷿");
	set("long", @LONG
���Ǵ�������������鷿����������һ����ľ�����Ϸ��Ų����飬
��ǽ�ĵط�����һ����ܣ����������������￴�顣
LONG);
	set("objects",([
		CLASS_D("duan") + "/zhu" : 1,
	]));
	set("exits", ([
		"west"  : __DIR__"tingfang",
	]));
	setup();
}
