// check recruit

int permit_recruit(object ob)
{
	if( ob->query("detach/Ѫ����") || ob->query("betrayer/Ѫ����") )
	{
		command("say ���뿪��Ѫ�����ǣ��ͱ������");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say ��ʦ֮ͽ���ߣ��ߣ��Ұ���ǧ����У�");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "Ѫ����" )
	{
		command("say �㲻���Ѿ�����ʦ��ô��������ʲô��͵ѧ�����ؼ�����");
		return 0;
	}

	return 1;
}
