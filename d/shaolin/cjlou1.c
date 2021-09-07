// Room: /d/shaolin/cjlou1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "�ؾ����¥");
	set("long", @LONG
ǧ������������ִ��ԭ����֮ţ�����Դ�Ħ�������£�����
�˲ı����������в��ٸ�ɮ�������棬�㼯�����ճ���������
��������ʮ�����ա����־����������ڴˡ���¥���濪����ȷ��
ͨ�硣�м����������Ŵ���ܡ���������а������Թ��Ķ�����
λ��ɮ��ִ�������ڱ�Ŀ��˼��
LONG );
	set("exits", ([
		"down" : __DIR__"cjlou",
	]));
	set("objects",([
		CLASS_D("shaolin") + "/hui-zhen" : 1,
		"/clone/book/wuji1" : 1,
		"/clone/book/wuji2" : 1,
		"/clone/book/wuji3" : 1,
	]));
	set("no_fight", 1);
	setup();

	if (random(5) == 0)
		"/clone/book/wuji4"->move(this_object());
}

int valid_leave(object me, string dir)
{
	object *ob;
	int i;


if ( present("shaolin wuji", me))
            return notify_fail("�书�ؼ�ֻ���ڲؾ�������ϰ������Я�������\n");

	if (dir != "down" || 
	    ! present("huizhen zunzhe", environment(me)))
		return ::valid_leave(me, dir);

	ob = deep_inventory(me);
	for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("shaolin wuji")) 
			return notify_fail("����˵�����书�ؼ�ֻ���ڲؾ�������ϰ������Я�������\n");
	return ::valid_leave(me, dir);
}

