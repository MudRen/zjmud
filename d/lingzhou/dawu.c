// dawu.c ���д��� 
inherit ROOM; 
	
void create() 
{ 
	set("short", "���д���"); 
	set("long", @LONG 
����һ��ԭľ�Ƴɵ�����ߴ���������ȥ����Щ���µ��Լ��
�쳣���ײ�����������ľ�ܿգ�һ��ľ��ͨ���¥����¥��¥���Ϲ�
��һ������һ�������Ĵ��죬����ȥ���ƾɲ���������ֻ֪��������
�ǽ����һ�������۵�С����
LONG 
	);
	set("exits", ([ 
		"west"     : __DIR__"kongdi", 
	])); 
	set("item_desc", ([ 
		"��С����" : "һ����ǽ�Ǳ����صúܺõ�С����\n"
		ZJOBACTS2"�궴:enter dong\n",
	])); 
	set("objects", ([ 
		 __DIR__"npc/ye" : 1,
	]));	
	setup(); 
} 
      
void init() 
{ 
	add_action("do_enter", "enter"); 
	add_action("do_enter", "zuan"); 
} 

int do_enter(string arg) 
{ 
	object me; 
	mapping fam; 
       
	me = this_player(); 
	if (! arg || arg == "") return 0; 
	if (arg == "dong") 
	{ 
		if (me->query("family/family_name") == "ؤ��")  
		{ 
			message("vision", me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��\n", environment(me), me); 
			me->move("/d/gaibang/underlz"); 
			message("vision", me->name() + "�Ӷ������˽�����\n", environment(me), ({me}) ); 
			return 1; 
		} 
		else  
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n"); 
	} 
} 


