-- ȫ�ֱ���
m_dir = 0.001;

-- ��ʼ��
function Init()
	-- ��ʼ��
	this:SetResPath("data\\m1\\General\\daodunbing.m1");

	-- ע�������¼�
	this:RegisterInputEvent( InputEvent:new( 1, 30));
	this:RegisterInputEvent( InputEvent:new( 2, 32));
	this:RegisterInputEvent( InputEvent:new( 3, 36));
end

-- ѭ��
function Loop( elapsedTime)

end

-- �����¼�
function ProcessEvent( ie)
	local pos = this:GetPosition();
	if( ie:GetID()==1) then
		m_dir = -0.01;
		pos.x = pos.x + m_dir;
		this:SetPosition( pos);
	end
	if( ie:GetID()==2) then
		m_dir = 0.01;
		pos.x = pos.x + m_dir;
		this:SetPosition( pos);
	end
	if( ie:GetID()==3) then
		this:PlayAnimation( "gongji01");
	end
end