// beidimiao.c  ������ 
inherit ROOM; 
void create() 
{ 
	set("short", "������"); 
	set("long", @LONG 
�������������ϡ�Ժ����һ����ˮ��������ʯ��ʯ�ߣ���Ȼ��
�ᡣ�������ʯ����Ѫ����Ȼ�������������ڴ�����С�ϸ��֮�£�
�������滹��һ��С����
LONG 
	);
	set("exits", ([ 
		"south" : __DIR__"street1", 
	])); 
	set("item_desc", ([ 
		"������" : "�����������ط·��и�С����\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
	set("no_fight", 1);
	set("valid_start_room", 1);
	set("no_sleep_room", 1);	
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
			message("vision", 
				me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��\n", 
				environment(me), me); 
			me->move("/d/gaibang/underfs"); 
			message("vision", 
				me->name() + "�Ӷ������˽�����\n", 
				environment(me), ({me}) ); 
			return 1; 
		} 
		else  
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n"); 
	} 
} 


