inherit ROOM;
void create()
{
	object item, con, jing, jian;

	set("short", "������¥����");
	set("long", @LONG
������������¥�Ĵ������൱�Ŀ���һ��������Ů�������ã���Ůǰ
����һ��޴�ĺ�ľ�������ܣ�����վ�����ױ����ų��������ɡ�
LONG );
	set("exits", ([ 
		"down" : __DIR__"was_lou3",
	]));
	set("objects", ([
		"/d/tulong/yitian/npc/ada" : 1,
		"/d/tulong/yitian/npc/aer" : 1,
		"/d/tulong/yitian/npc/asan" : 1,
		"/d/tulong/yitian/npc/he" : 1,
		"/d/tulong/yitian/npc/zhao" : 1,
		"/d/tulong/yitian/obj/shelf" : 1,
	]) );
	set("action_list", ([
		"����":"bi",
	]));
	setup();
	jian = find_object("/d/tulong/obj/yitianjian");
	jing = find_object("/d/tulong/obj/zhenjing");
	if (	(!jian||!environment(jian)) && (!jing||!environment(jing)) ) {
		con = present( "shelf", this_object());
		if(!jian) jian = load_object("/d/tulong/obj/yitianjian");
		if(con&&jian) jian->move(con);
	}
}
